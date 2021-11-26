#include "include/Camera.h"

void Camera::init()
{
	play_oscillation = false;
	oscillation_amplitude = 2.0f;
}

void Camera::update()
{
	if (play_oscillation)
	{
		current_time = SDL_GetTicks();

		int elapsed = current_time - start_time;

		srand(elapsed);

		float x = ((float)rand() / (float)RAND_MAX - 0.5f) * 2.0f;
		x *= oscillation_amplitude;
		float y = ((float)rand() / (float)RAND_MAX - 0.5f) * 2.0f;
		y *= oscillation_amplitude;

		Translate(x, y);

		if (elapsed > oscillation_duration * 1000)
			play_oscillation = false;
	}
}

void Camera::PlayCameraShake()
{ 
	start_time = SDL_GetTicks();
	play_oscillation = true;
}
