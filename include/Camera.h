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
	void SetWidth(float x) { camera_rect.w = x; }
	float GetWidth() const { return camera_rect.w; }
	float GetHeight() const { return camera_rect.h; }
	void SetHeight(float y) { camera_rect.h = y; }
	void SetViewOffset(float _offset) { offset = _offset; }
	SDL_FPoint GetPos() const { return SDL_FPoint{ camera_rect.x, camera_rect.y }; }

private:
	SDL_FRect camera_rect;
	float offset;
};

#endif //CAMERA_H