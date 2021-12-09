// Base class for maintaining global application state
#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <vector>

#include "Global.h"
#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"
#include "TextHandler.h"

class Application
{
public:
	Application(const std::string& name = "CPSC-6041");
	virtual ~Application();

	void init();

	void loop();

	void handle_events();

	void update_mechanics();

	void redner();

	void framerate();

	bool get_game_is_running() { return is_running; }

	void quit();

	void set_is_game_over(const int& go);

private:
	bool is_running;
	bool is_paused;

	//0 = normal; 1 = title; 2 = game over
	int is_game_over;
	SDL_Window* my_window;
	SDL_Renderer* my_renderer;

	int start_time;
	int last_count_start_time;
	int fps;
	int frame_duration;

	SDL_Event ev;

	SDL_Texture* my_texture;
	SDL_Rect rect;

	Scene* current_scene;

	TextHandler* pause_menu;
	SDL_Rect pause_rect;

	SDL_Rect menu_background;
	Image* end_background;

	TextHandler* title_menu;
	SDL_Rect title_rect;

	TextHandler* subtitle_menu;
	SDL_Rect subtitle_rect;

	TextHandler* gameover_menu;
	SDL_Rect gameover_rect;
};

#endif //APPLICATION_H