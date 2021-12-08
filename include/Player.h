#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"


// Player Declaration:
// Base class for movable character
class Player : public Character
{
public:
	Player(float x, float y, const char* imageName = nullptr) :
		Character(x, y, imageName)
	{
		key_pressed = false;
		SetPosition(x, y);
		velocity_x = 0.0f;
		velocity_x = 0.f;
		flip_sprite = SDL_FLIP_NONE;
		score = 0;
	}

	virtual ~Player() {}

	virtual void init();
	virtual void update();
	virtual void render(SDL_Renderer* ren);
	virtual void handle_events(SDL_Event& ev);

	virtual void SetVel(const float x, const float y)
	{
		velocity_x = x;
		velocity_y = y;
	};

	SDL_FPoint GetDirectionToMouse(const int x, const int y) const;

	// UI interface
	void UpdateHealthBar(int _health);
	int GetRiceScore() { return 0; }
	int GetCarrotScore() { return 0; }
	int GetSushiScore() { return 0; }
	bool GetIsDead() {return is_dead;}

	// collision
	virtual void CollisionResponse(GameObject* other);

private:
	void Died();

private:
	int full_health;
	int score;
	bool is_dead;
	Weapon* weapon;
	HealthBar* health_bar;
};

#endif	//PLAYER_H