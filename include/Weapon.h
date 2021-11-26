#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"


class Bullet : public TextureObject
{
public:
	Bullet(const char* name, float x, float y);

	virtual void init();
	virtual void update();
	virtual void handle_events(SDL_Event& ev) {}

	void SetSpeed(const float& _speed) { speed = _speed; }
	float GetSpped() const { return speed; }

	void SetDirection(const SDL_FPoint& _dir) { direction = _dir; }
	SDL_FPoint GetDirection() const { return direction; }

private:
	float speed;
	SDL_FPoint direction;
};

class Weapon : public TextureObject
{
public:
	Weapon(const char* name, float x, float y);

	void SetMuzzlePosition(const SDL_FPoint& _pos);
	SDL_FPoint GetMuzzlePosition();

	void SetSpeed(const float& _speed) { speed = _speed; }
	float GetSpped() const { return speed; }

	void Fire(const SDL_FPoint& dir);

protected:
	SDL_FPoint muzzle;
	float speed;
};

#endif // WEAPON_H
