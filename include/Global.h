// Class that holds global variable
#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <iostream>


class Camera;
class Scene;
class Map;
class Player;

// Global class hold global setting, such as renderer and window
class Global
{
public:
	static Global* GetInstance()
	{
		if (my_global == nullptr)
			my_global = new Global;
		return my_global;
	}

	Global(Global const&) = delete;
	void operator=(Global const&) = delete;

	static SDL_Renderer* GetRenderer() { return my_renderer; }
	static void SetRenderer(SDL_Renderer* renderer) { my_renderer = renderer; }

	static SDL_Window* GetWindow() { return my_window; }
	static void SetWindow(SDL_Window* window) { my_window = window; }

	static const int GetWindowWidth() { return SCREEN_WIDTH; }
	static const int GetWindowHeight() { return SCREEN_HEIGHT; }

	static void SetMainCamera(Camera* _cam) { main_camera = _cam; }
	static Camera* GetMainCamera() { return main_camera; }

	static Scene* GetActiveScene() { return active_scene; }
	static void SetActiveScene(Scene* _scene) { active_scene = _scene; }

	static Map* GetActiveMap() { return active_map; }
	static void SetActiveMap(Map* _map) { active_map = _map; }

	static Player* GetMainPlayer() { return main_player; }
	static void SetMainPlayer(Player* _player) { main_player = _player; }
	
private:
	Global()
	{
		main_camera = nullptr;
	}
	static Global* my_global;
	static SDL_Window* my_window;
	static SDL_Renderer* my_renderer;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static Camera* main_camera;
	static Scene* active_scene;
	static Map* active_map;
	static Player* main_player;
};

#endif // GLOBAL_H