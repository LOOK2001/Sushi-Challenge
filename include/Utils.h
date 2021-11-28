#ifndef UTILS_H
#define UTILS_H

#include "GameObject.h"
#include "Scene.h"

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

	static SDL_FPoint RotatePoint(const SDL_FPoint& point, const float& angle, const SDL_FPoint& center)
	{
		float radian = angle * PI / 180.f;
		float x = (point.x - center.x) * cos(radian) - (point.y - center.y) * sin(radian) + center.x;
		float y = (point.y - center.y) * cos(radian) + (point.x - center.x) * sin(radian) + center.y;
		return { x, y };
	}

	static SDL_FPoint Lerp(SDL_FPoint a, SDL_FPoint b, float t)
	{
		return { (1 - t) * a.x + t * b.x, (1 - t) * a.y + t * b.y };
	}
}

static float Distance(SDL_FPoint p1, SDL_FPoint p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

static void DeleteObjet(GameObject* obj)
{
	Scene* s = Global::GetActiveScene();
	s->RemoveGameObject(obj);
}

static void AddInstance(GameObject* obj)
{
	Scene* s = Global::GetActiveScene();
	s->AddGameObject(obj);
}

#endif //UTILS_H