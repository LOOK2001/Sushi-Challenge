// Class for maintaining character state such translation and character state
#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>

#include "GameObject.h"
#include "Sprite.h"
#include "Global.h"
#include "Weapon.h"


// Class to display the health bar
class HealthBar : public RectFillObject
{
public:
	HealthBar(float x, float y, float w, float h)
	{
		SetPosition(x, y);
		SetWidth(w);
		SetHeight(h);
		precentage = 0.0;
		back = front = nullptr;
	}
	virtual ~HealthBar()
	{
		if (back)
			delete back;
		if (front)
			delete front;
	}

	virtual void init();
	virtual void render(SDL_Renderer* ren);

	SDL_Color GetBackColor() const { return back->getColor(); }
	SDL_Color GetFrontColor() const { return front->getColor(); }
	void SetBackColor(const SDL_Color& _color) { back->setColor(_color); }
	void SetFrontColor(const SDL_Color& _color) { front->setColor(_color); }

	void SetPrecentage(const float& _p);
	float GetPrecentage() const { return precentage; }

private:
	RectFillObject* back;
	RectFillObject* front;
	float precentage;
};


// Base class for movable character like enemy and player
class Character : public RectObject
{
public:
	Character(float x, float y, const char* imageName = nullptr)
	{
		SetPosition(x, y);
		velocity_x = 0.0f;
		velocity_x = 0.f;
		flip_sprite = SDL_FLIP_NONE;
		current_state = "none";
		speed = 10.0f;
		health = 0;
	}
	virtual ~Character() {}

	virtual void init();
	virtual void update();
	virtual void render(SDL_Renderer* ren);
	virtual void handle_events(SDL_Event& ev);
	virtual void quit()
	{
		std::map<std::string, SpriteObject*>::iterator  it;
		for (it = state.begin(); it != state.end(); it++)
		{
			delete it->second;
		}
		RectObject::quit();
	}

	virtual void AddState(SpriteObject* sprite_anim, std::string _state);
	virtual void SwitchState(std::string _state);
	virtual void SetDefaultState(std::string _state);

	// The velocity will be used by the enemy
	virtual void SetVel(const float x, const float y)
	{
		velocity_x = x;
		velocity_y = y;
	};
	virtual void GetVel(float& x, float& y) { x = velocity_x, y = velocity_y; };

	// The speed will be used by the player
	virtual void SetSpeed(const float& _speed) { speed = _speed; }
	virtual float GetSpeed() const { return speed; }

	virtual void SetHealth(const int& _health) { health = _health; }
	virtual int GetHealth() { return health; }


protected:
	float velocity_x;
	float velocity_y;
	SDL_RendererFlip flip_sprite;
	std::map<std::string, SpriteObject*> state;
	std::string current_state;
	float speed;
	int health;
};

#endif // CHARACTER_H
