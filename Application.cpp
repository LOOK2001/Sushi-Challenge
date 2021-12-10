
#include "include/Application.h"


Application::Application(const std::string& name /*= "CPSC-6041"*/)
{
	is_running = false;
	is_paused = false;
	my_window = nullptr;
	my_renderer = nullptr;
	my_texture = nullptr;
	pause_menu = nullptr;

	is_game_over = 1;

	fps = 60;
	frame_duration = 1000 / fps;

	current_scene = new ExampleScene(this);
	Global::SetActiveScene(current_scene);
}

Application::~Application()
{
	if (my_window)
		SDL_DestroyWindow(my_window);

	if (my_renderer)
		SDL_DestroyRenderer(my_renderer);

	if (current_scene)
		delete current_scene;

	if (end_background)
		delete end_background;
}

void Application::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

	// Enable gpu_enhanced textures
	IMG_Init(IMG_INIT_PNG);

	is_running = true;

	const int SCREEN_WIDTH = Global::GetWindowWidth();
	const int SCREEN_HEIGHT = Global::GetWindowHeight();

	my_window = SDL_CreateWindow("my_game",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							SCREEN_WIDTH,
							SCREEN_HEIGHT, 0);

	Global::SetWindow(my_window);

	my_renderer = SDL_CreateRenderer(Global::GetWindow(), -1, 0);

	Global::SetRenderer(my_renderer);

	SDL_SetRenderDrawBlendMode(my_renderer, SDL_BLENDMODE_BLEND);

	//Create Pause Text
	pause_menu = new TextHandler();
	SDL_Color pause_color = {0,0,0};
	pause_menu->text_init(my_renderer, "./images/fonts/cookiemilkFont.ttf", (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), pause_color, 96);
	pause_menu->text_update("Paused");
	pause_rect.x = SCREEN_WIDTH/2;
	pause_rect.y = SCREEN_HEIGHT/2;
	pause_rect.w = 100;
	pause_rect.h = 32;

	//Set is_game_over to 1 for title display upon initialization
	is_game_over = 1;

	menu_background.x = 0;
	menu_background.y = 0;
	menu_background.w = Global::GetWindowWidth();
	menu_background.h = Global::GetWindowHeight();

	end_background = new Image("./images/TheEnd.png");

	//Create Title
	title_menu = new TextHandler();
	SDL_Color title_color = {65, 105, 225};
	title_menu->text_init(my_renderer, "./images/fonts/cookiemilkFont.ttf", (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), title_color, 48);
	title_menu->text_update("Sushi Challenge");
	title_rect.x = SCREEN_WIDTH/2;
	title_rect.y = SCREEN_HEIGHT/2;
	title_rect.w = 100;
	title_rect.h = 32;

	//Create Title
	subtitle_menu = new TextHandler();
	SDL_Color subtitle_color = {65, 105, 225};
	subtitle_menu->text_init(my_renderer, "./images/fonts/cookiemilkFont.ttf", (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2) + 48, subtitle_color, 12);
	subtitle_menu->text_update("Press any key to continue");
	subtitle_rect.x = SCREEN_WIDTH/2;
	subtitle_rect.y = SCREEN_HEIGHT/2;
	subtitle_rect.w = 100;
	subtitle_rect.h = 32;

	//Create Game Over
	gameover_menu = new TextHandler();
	SDL_Color gameover_color = {178, 34, 34};
	gameover_menu->text_init(my_renderer, "./images/fonts/cookiemilkFont.ttf", (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), gameover_color, 96);
	gameover_menu->text_update("Game Over");
	gameover_rect.x = SCREEN_WIDTH/2;
	gameover_rect.y = SCREEN_HEIGHT/2;
	gameover_rect.w = 100;
	gameover_rect.h = 32;

	current_scene->init();
}

void Application::loop()
{
	while (get_game_is_running())
	{
		handle_events();
		update_mechanics();
		redner();
		framerate();
	}
}

void Application::handle_events()
{
	while (SDL_PollEvent(&ev) != 0) {

		if (ev.type == SDL_QUIT)
			is_running = false;
		else if (ev.type == SDL_KEYDOWN)
		{
			if(is_game_over == 0)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_ESCAPE:
				case SDLK_q:
					is_running = false;
					break;
				case SDLK_SPACE:
					if(is_paused) {
						is_paused = false;
					}
					else{
						is_paused = true;
					}
				}
			}
			else if(is_game_over == 1){
				is_game_over = 0;
			}
			else if(is_game_over >= 2){
				is_game_over = 1;
				is_paused = false;
				Scene* _scene = Global::GetActiveScene();
				if (_scene)
				{
					_scene->quit();
					//delete _scene;
				}
					
				current_scene = new ExampleScene(this);
				Global::SetActiveScene(current_scene);
				current_scene->init();
			}
		}
		if(!is_paused) {
			current_scene->handle_events(ev);
		}
	}
}

void Application::update_mechanics()
{
	if(Global::GetMainPlayer()->GetIsDead() == true)
	{
		is_game_over = 2;
		is_paused = true;
	}
	if(!is_paused && is_game_over == 0) {
		current_scene->update();
		current_scene->lateUpdate();
	}
}

void Application::redner()
{
	if(is_game_over == 1)
	{
		SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(my_renderer, &menu_background);
		title_menu->text_render(title_rect);
		subtitle_menu->text_render(subtitle_rect);
	}
	else if(is_game_over == 2)
	{
		current_scene->render(my_renderer);
		SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, 125);
		SDL_RenderFillRect(my_renderer, &menu_background);
		gameover_menu->text_render(gameover_rect);
		subtitle_menu->text_render(subtitle_rect);
	}
	else if (is_game_over == 3)
	{
		SDL_FPoint pos = Global::GetMainCamera()->GetPos();
		end_background->Draw(pos.x, pos.y, 0.0, nullptr);
	}
	else
	{
		current_scene->render(my_renderer);
		if(is_paused){
			//render pause menu
			pause_menu->text_render(pause_rect);
		}
	}
	SDL_RenderPresent(my_renderer);
}

void Application::framerate()
{
	static int duration, fpsCounter;

	start_time = SDL_GetTicks();
	fpsCounter++;

	if (start_time >= (last_count_start_time + 1000)) {
		last_count_start_time = start_time;
		fps = fpsCounter;
		fpsCounter = 0;
	}

	// make sure fixed frame rate
	if (duration < frame_duration) {
		SDL_Delay(frame_duration - duration);
	}
}

void Application::quit()
{
	SDL_DestroyRenderer(my_renderer);
	SDL_DestroyWindow(my_window);

	current_scene->quit();

	IMG_Quit();
	SDL_Quit();
}

void Application::set_is_game_over(const int& go)
{
	is_game_over = go;
}
