// Class for maintaining character state such translation and character state
#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>

#include "GameObject.h"
#include "Sprite.h"
#include "Global.h"


enum CtrlMode
{
	POSITION,
	VELOCITY
};


// Player Declaration:
// Base class for movable character
class Player : public RectObject
{
public:
	Player(float x, float y, float w, float h, unsigned count, double duration, const char* imageName = nullptr)
	{
		key_pressed = false;
		SetPosition(x, y);
		setSize(w, h);
		velocity_x = 0.0f;
		velocity_x = 0.f;
		flip_sprite = SDL_FLIP_NONE;
	}

	virtual ~Player() {}

	virtual void init();
	virtual void update();
	virtual void render(SDL_Renderer* ren);
	virtual void handle_events(SDL_Event& ev);

	void set_vel(const float x, const float y)
	{
		velocity_x = x;
		velocity_y = y;
	};
	void get_vel() {};

	void AddState(SpriteObject* sprite_anim, std::string _state);
	void SwitchState(std::string _state);
	void SetDefaultState(std::string _state);

	// collision
	virtual void CollisionResponse(GameObject* other);

private:
	bool key_pressed;
	float velocity_x;
	float velocity_y;
	SDL_RendererFlip flip_sprite;
	std::map<std::string, SpriteObject*> state;
	std::string current_state;
	bool draw_skin;
	SDL_Color skin_color;
};

#endif // CHARACTER_H
