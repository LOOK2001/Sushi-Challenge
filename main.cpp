#include "include/Application.h"

using namespace std;

int main(int argc, char* argv[])
{
	Application* app = new Application();
	
	// Initialize renderer and window setting
	app->init();

	// Game loop
	app->loop();

	app->quit();

	return 0;
}
