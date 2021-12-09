// Class the stores the view of player such as position and width and height
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "GameObject.h"
#include "Global.h"
#include "Image.h"


class Camera : public GameObject
{
public:
	Camera(float _x, float _y, float _w, float _h) :
		offset(50.0f)
	{
		camera_rect = { _x, _y, _w, _h };
	}
	~Camera(){}

	virtual void init();
	virtual void update();
	virtual void lateUpdate();

	bool IsInsideView(const float x, const float y)
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
					world_y >= area.y && world_y <= area.y+ area.h))
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
		else if(currentLevel == 0) {
				std::vector<SDL_FRect> areas = GetLevelArea(currentLevel);
				bool flag = false;
				for (int i = 0; i < areas.size(); i++)
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

	void SetPos(float x, float y) { camera_rect.x = x, camera_rect.y = y; }
	void SetPos(const SDL_FPoint& _pos) { camera_rect.x = _pos.x, camera_rect.y= _pos.y; }
	SDL_FPoint GetPos() const { return SDL_FPoint{ camera_rect.x, camera_rect.y }; } 

	void Translate(float _x, float _y) { camera_rect.x += _x, camera_rect.y += _y; }

	void SetWidth(float x) { camera_rect.w = x; }
	float GetWidth() const { return camera_rect.w; }

	void SetHeight(float y) { camera_rect.h = y; }
	float GetHeight() const { return camera_rect.h; }

	void SetViewOffset(float _offset) { offset = _offset; }
	float GetViewOffset() const { return offset; }

	void SetTarget(GameObject* _target) { target = _target; }
	GameObject* GetTarget() const { return target; }

	void SetTargetOffset(const SDL_FPoint& offset) { target_offset = offset; }
	SDL_FPoint GetTargetOffset() { return target_offset; }

	void SetCurrentLevel(const int& level) { currentLevel = level; }
	int GetCurrentLevel() const { return currentLevel; }

	void InsertLevelArea(const int& levelIdx, SDL_FRect area);
	const std::vector<SDL_FRect>& GetLevelArea (const int& levelIdx);
	
	// Camera Shake
	void PlayCameraShake();
	float GetoOcillationDuration() const { return oscillation_duration; }
	void SetOcillationDuration(const float& _duration) { oscillation_duration = _duration; }
	float GetOcillationAmplitude() { return oscillation_amplitude; }
	void SetOcillationAmplitude(const float& _amplitude) { oscillation_amplitude = _amplitude; }
	
private:
	GameObject* target;
	SDL_FPoint target_offset;
	float smooth_speed;
	SDL_FRect camera_rect;
	int start_time;
	int current_time;
	float offset;
	bool play_oscillation;
	float oscillation_duration;
	float oscillation_amplitude;
	int currentLevel;
	std::unordered_map<int, std::vector<SDL_FRect>> level_area;
};

#endif //CAMERA_H