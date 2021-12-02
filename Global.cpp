
#include "include/Global.h"

// Initialize global setting
Global* Global::my_global = nullptr;
SDL_Window* Global::my_window = nullptr;
SDL_Renderer* Global::my_renderer = nullptr;
int Global::SCREEN_WIDTH = 640;
int Global::SCREEN_HEIGHT = 480;
Camera* Global::main_camera = nullptr;
Scene* Global::active_scene = nullptr;
Map* Global::active_map = nullptr;
Player* Global::main_player = nullptr;