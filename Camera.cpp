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
	// Camera shake effect
	if (play_oscillation)
	{
		// Random position for camera each frame
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

bool Camera::IsInsideView(const float x, const float y)
{
	// World space
	SDL_FPoint _pos = GetPos();
	float world_x = x + _pos.x;
	float world_y = y + _pos.y;

	if (currentLevel != 0)
	{
		SDL_FRect area = GetLevelArea(currentLevel)[0];
		if (currentLevel == 1)
		{
			if (!(world_x >= area.x && world_x <= area.x + area.w &&
				world_y >= area.y && world_y <= area.y + area.h))
				return false;
		}
		else if (currentLevel == 2)
		{
			if (!(world_x >= area.x && world_x <= area.x + area.w &&
				world_y >= area.y && world_y <= area.y + area.h))
				return false;
		}
		else if (currentLevel == 3)
		{
			if (!(world_x >= area.x && world_x <= area.x + area.w &&
				world_y >= area.y && world_y <= area.y + area.h))
				return false;
		}
	}
	else if (currentLevel == 0) {
		std::vector<SDL_FRect> areas = GetLevelArea(currentLevel);
		bool flag = false;
		for (size_t i = 0; i < areas.size(); i++)
		{
			SDL_FRect area = areas[i];
			if ((world_x >= area.x && world_x <= area.x + area.w &&
				world_y >= area.y && world_y <= area.y + area.h))
			{
				flag = true;
				break;
			}

		}
		if (!flag)
			return false;
	}

	float min_x = -offset;
	float max_x = camera_rect.w + offset;
	float min_y = -offset;
	float max_y = camera_rect.h + offset;

	if (x >= min_x && x <= max_x
		&& y >= min_y && y <= max_y)
		return true;
	return false;
}

void Camera::InsertLevelArea(const int& levelIdx, SDL_FRect _area)
{
	std::vector<SDL_FRect> areas = level_area[levelIdx];

	for (size_t i = 0; i < areas.size(); i++)
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
