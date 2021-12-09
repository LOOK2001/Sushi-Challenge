#include "include/Camera.h"
#include "include/Utils.h"

void Camera::init()
{
	play_oscillation = false;
	oscillation_amplitude = 2.0f;
	smooth_speed = 0.125f;
}

void Camera::update()
{
	// Camera follow the player
	SDL_FPoint pos = target->GetGlobalPosition();
	// Get camera target position w, h
	float w = GetWidth() / 2;
	float h = GetHeight() / 2;

	// Move camera on top of character
	SetPos(pos.x - w + target_offset.x, pos.y - h + target_offset.y);
}

void Camera::lateUpdate()
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

	// Smooth camera
	//SDL_FPoint target_pos = target->GetGlobalPosition();
	//SDL_FPoint camera_pos = Global::GetMainCamera()->GetPos();

	//// Get camera target position w, h
	//float w = GetWidth() / 2;
	//float h = GetHeight() / 2;
	//target_pos = { target_pos.x - w + target_offset.x, target_pos.y - h + target_offset.y };

	//SDL_FPoint pos = Vector2D::Lerp(camera_pos, target_pos, smooth_speed);
	//SetPos(pos);
}

void Camera::InsertLevelArea(const int& levelIdx, SDL_FRect _area)
{
	std::vector<SDL_FRect> areas = level_area[levelIdx];

	for (int i = 0; i < areas.size(); i++)
	{
		if (areas[i].x == _area.x && areas[i].y == _area.y &&
			areas[i].w == _area.w && areas[i].h == _area.h)
		{
			return;
		}
	}
	level_area[levelIdx].push_back(_area);
}

const std::vector<SDL_FRect>& Camera::GetLevelArea(const int& levelIdx)
{
	if (level_area.count(levelIdx))
	{
		return level_area[levelIdx];
	}
	return std::vector<SDL_FRect>();
}

void Camera::PlayCameraShake()
{ 
	start_time = SDL_GetTicks();
	play_oscillation = true;
}
