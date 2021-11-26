// Class the stores the view of player such as position and width and height
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

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

	bool IsInsideView(const float x, const float y) const
	{
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
	SDL_FPoint GetPos() const { return SDL_FPoint{ camera_rect.x, camera_rect.y }; } 

	void Translate(float _x, float _y) { camera_rect.x += _x, camera_rect.y += _y; }

	void SetWidth(float x) { camera_rect.w = x; }
	float GetWidth() const { return camera_rect.w; }

	void SetHeight(float y) { camera_rect.h = y; }
	float GetHeight() const { return camera_rect.h; }

	void SetViewOffset(float _offset) { offset = _offset; }

	// Camera Shake
	void PlayCameraShake();
	float GetoOcillationDuration() const { return oscillation_duration; }
	void SetOcillationDuration(const float& _duration) { oscillation_duration = _duration; }
	float GetOcillationAmplitude() { return oscillation_amplitude; }
	void SetOcillationAmplitude(const float& _amplitude) { oscillation_amplitude = _amplitude; }
	
private:
	SDL_FRect camera_rect;
	int start_time;
	int current_time;
	float offset;
	bool play_oscillation;
	float oscillation_duration;
	float oscillation_amplitude;
};

#endif //CAMERA_H