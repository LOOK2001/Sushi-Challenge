#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"


class Bullet : public TextureObject
{
public:
	Bullet(const char* name, float x, float y);

	virtual void update() {};

private:
	float speed;
	SDL_FPoint direction;


};

class Weapon : public TextureObject
{
public:
	Weapon(const char* name, float x, float y);

	void Fire();
protected:
private:
};

#endif // WEAPON_H
