#ifndef UTILS_H
#define UTILS_H

#include "GameObject.h"

namespace Vector2D
{
	static float Length(const SDL_FPoint& _vec)
	{
		return sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
	}

	static SDL_FPoint normal(const SDL_FPoint& _vec)
	{
		float len = Length(_vec);
		SDL_FPoint norm;
		if (len > 0)
			norm = { _vec.x / len, _vec.y / len };
		return norm;
	}

	static float Angle(const SDL_FPoint& _vec)
	{
		return atan2(_vec.y, _vec.x);
	}
}

static float Distance(SDL_FPoint p1, SDL_FPoint p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

#endif //UTILS_H