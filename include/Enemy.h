#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Weapon.h"

class SushiBoss : public Character
{
public:
	SushiBoss(float x, float y, const char* imageName = nullptr) :
		Character(x, y, imageName)
	{
		srand(35);
		velocity_x = velocity_y = 1.0f;
		player = nullptr;
		range = 200.0f;
		start_time = 0;
		last_time = 0;
		decayrate = 0.95f;
		hit_color[0] = hit_color[1] = hit_color[2] = hit_color[3] = 0.0f;
	}

	virtual void init();
	virtual void update();
	virtual void render(SDL_Renderer* ren);

	void SetHitColor(const float& r, const float& g, const float& b, const float& a);

	// collision
	virtual void CollisionResponse(GameObject* other);

	void FindPlayer()
	{
		// Initialize the open and closed list
		std::vector<int> open_list;
		std::vector<int> closed_list;
	}

private:
	void Decay(SDL_Renderer* ren);

protected:
	float range;
	Player* player;
	int start_time;
	int last_time;
	float decayrate;
	float hit_color[4];
};

#endif