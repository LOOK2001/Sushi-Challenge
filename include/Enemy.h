#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Weapon.h"
#include "StateMachine.h"

class Enemy : public Character
{
public:
	Enemy(float x, float y) : 
		Character(x, y)
	{
		srand(35);
		velocity_x = velocity_y = 1.0f;
		player = nullptr;
		range = 250.0f;
		start_time = 0;
		last_time = 0;
		decayrate = 0.95f;
		hit_color[0] = hit_color[1] = hit_color[2] = hit_color[3] = 0.0f;
	}

	virtual void init();
	virtual void update();
	virtual void render(SDL_Renderer* ren);

	void SetHitColor(const float& r, const float& g, const float& b, const float& a);
	void SetRange(const float& _range) { range = _range; }
	float GetRange() { return range; }

	void GetInitVel(float& x, float& y) { x = init_velocity_x, y = init_velocity_y; };

	// collision
	virtual void CollisionResponse(GameObject* other);

private:
	virtual void Decay(SDL_Renderer* ren);

protected:
	float init_velocity_x;
	float init_velocity_y;
	float range;
	Player* player;
	int start_time;
	int last_time;
	float decayrate;
	float hit_color[4];
	StateMachine* stateMachine;
};

class SushiBoss : public Enemy
{
public:
	SushiBoss(float x, float y) :
		Enemy(x, y)
	{
		srand(35);
		velocity_x = velocity_y = 1.0f;
		player = nullptr;
		range = 1000.0f;
		start_time = 0;
		last_time = 0;
		decayrate = 0.95f;
		hit_color[0] = hit_color[1] = hit_color[2] = hit_color[3] = 0.0f;
	}

	virtual void update();

	// collision
	virtual void CollisionResponse(GameObject* other);

private:
	virtual void Decay(SDL_Renderer* ren);
};

#endif