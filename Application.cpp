
#include "include/Application.h"


Application::Application(const std::string& name /*= "CPSC-6041"*/)
{
	is_running = false;
	my_window = nullptr;
	my_renderer = nullptr;
	my_texture = nullptr;

	fps = 60;
	frame_duration = 1000 / fps;

	current_scene = new SceneHw4();
	Global::SetActiveScene(current_scene);
}

Application::~Application()
{
	if (my_window)
		SDL_DestroyWindow(my_window);

	if (my_renderer)
		SDL_DestroyRenderer(my_renderer);
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
			switch (ev.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			case SDLK_q:
				is_running = false;
				break;
			}
		}
		current_scene->handle_events(ev);
	}
}

void Application::update_mechanics()
{
	current_scene->update();
}

void Application::redner()
{
	current_scene->render(my_renderer);

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
