#include "include/Weapon.h"
#include "include/Utils.h"


Bullet::Bullet(const char* name, float x, float y) :
	TextureObject(name, x, y)
{
}

void Bullet::init()
{
	TextureObject::init();

	type = ObjectType::BULLET;
	life_time = 100;
}

void Bullet::update()
{
	if (life_time <= 0)
	{
		DeleteObject(this);
	}

	Translate(direction.x * speed, direction.y * speed);
	life_time--;
}


Bomb::Bomb(const char* name, float x, float y) :
	Bullet(name, x, y)
{

}


void Bomb::init()
{
	Bullet::init();
	SetCollidable(false);
}

void Bomb::update()
{
	if (life_time <= 0)
	{
		// Blast
		SDL_FPoint pos = GetGlobalPosition();
		Bullet* blast = new Bullet("./images/bomb2.png", pos.x, pos.y);
		blast->SetLiftime(1500);
		blast->init();
		blast->SetObjectType(ObjectType::BLAST);
		AddInstance(blast);

		DeleteObject(this);
	}

	Translate(direction.x * speed, direction.y * speed);
	life_time--;
}

Weapon::Weapon(const char* name, float x, float y) :
	TextureObject(name, x, y)
{

}

void Weapon::SetMuzzlePosition(const SDL_FPoint& _pos)
{
	muzzle = _pos;
}

SDL_FPoint Weapon::GetMuzzlePosition()
{
	// Get the muzzle position based on the rotation and parent's position
	float angle = GetAngle();
	SDL_FPoint center = GetCenter();
	SDL_FPoint pos = Vector2D::RotatePoint(muzzle, angle, center);
	SDL_FPoint global = GetGlobalPosition();
	return { pos.x + global.x, pos.y + global.y };
}

void Weapon::Fire(const SDL_FPoint& dir)
{
	// Get the starting position
	SDL_FPoint muzzle = GetMuzzlePosition();
	// Create the bullet object
	Bullet* bullet = new Bullet("./images/particle.png", muzzle.x, muzzle.y);
	bullet->init();
	bullet->SetDirection(dir);
	bullet->SetSpeed(speed);
	// Add the bullet instance into the active scene
	AddInstance(bullet);
}
