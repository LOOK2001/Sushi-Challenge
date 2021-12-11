#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameObject.h"
#include "Image.h"


// Class that maintaining particle
class Particle : public RectObject 
{
public:
	Particle() {};
	~Particle() 
	{
		if (img)
			delete img;
	}

	void init(const char* graphics, SDL_Renderer* ren, int start_x, int start_y, int width, int height);
	void update();
	void render(SDL_Renderer* ren);

	void set_x_vel(float _vel) { x_vel = _vel; }
	void set_y_vel(float _vel) { y_vel = _vel; }
	void set_lifetime(int _time) { lifetime = _time; }

private:
	void obj_update_blow(){}

	float x_vel;
	float y_vel;

	int state;
	int lifetime;

	Image* img;
};

#endif // PARTICLE_H