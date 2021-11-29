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

private:
	bool is_running;
	bool is_paused;
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
};

#endif //APPLICATION_H