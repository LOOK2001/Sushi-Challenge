#ifndef PICKUP_H
#define PICKUP_H

#include <iostream>

#include "Sprite.h"
#include "ParticleEmitter.h"


class Pickup : public RectObject
{
public:
	Pickup(float _x, float _y, const char* imageName)
	{
		sprite = new SpriteObject(1, 100.0, imageName);
		rect.x = _x;
		rect.y = _y;
		rect.w = (float)sprite->GetViewWidth();
		rect.h = (float)sprite->GetViewHeight();
	}
	~Pickup()
	{
		if (sprite)
			delete sprite;
	}

	virtual void init();
	virtual void update();
	virtual void render(SDL_Renderer* ren);

	void SetCount(const int count);
	void SetDuration(const double duration) { sprite->SetDuration(duration); }

	// collision
	virtual void CollisionResponse(GameObject* other);

private:
	SpriteObject* sprite;
	ParticleEmitter* pe;
};


class Portal : public Pickup
{
public:
	Portal(float _x, float _y, const char* imageName) :
		Pickup(_x, _y, imageName)
	{}

	// collision
	virtual void CollisionResponse(GameObject* other);
};

#endif //PICKUP_H
