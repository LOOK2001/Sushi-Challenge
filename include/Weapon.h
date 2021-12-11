#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"


// Class that maintaining bullet data like speed, direction and lifetime
class Bullet : public TextureObject
{
public:
	Bullet(const char* name, float x, float y);

	virtual void init();
	virtual void update();
	virtual void handle_events(SDL_Event& ev) {}
	virtual void render(SDL_Renderer* ren)
	{
		TextureObject::render(ren);
	}

	virtual void SetSpeed(const float& _speed) { speed = _speed; }
	virtual float GetSpped() const { return speed; }

	virtual void SetDirection(const SDL_FPoint& _dir) { direction = _dir; }
	virtual SDL_FPoint GetDirection() const { return direction; }

	virtual void SetLiftime(const int& _time) { life_time = _time; }
	virtual int GetLifttime() const { return life_time; }

protected:
	float speed;
	SDL_FPoint direction;
	int life_time;
};


// Class that maintaining bomb
class Bomb : public Bullet
{
public:
	Bomb(const char* name, float x, float y);

	virtual void init();
	virtual void update();
};


// Class that maintaining weapon. Weapon can fire bullets
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
