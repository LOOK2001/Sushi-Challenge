#include "include/ParticleEmitter.h"

void ParticleEmitter::init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_width, int start_height, int type)
{
	GameObject::init();

	srand(5);
	part_type = type;
	particles.resize(MAX_PARTS);

	for (unsigned int i = 0; i < particles.size(); i++)
	{
		particles[i] = new Particle();
		particles[i]->init(graphic, ren, start_x, start_y, start_width, start_height);

		particles[i]->set_x_vel(3.0 - (rand() % 60) / 10.0);
		particles[i]->set_y_vel(0.0 - (rand() % 60) / 10.0);
		particles[i]->set_lifetime(30 + (rand() % 10));
	}
	is_running = false;
}

void ParticleEmitter::update()
{
	if (!is_running)
		return;

	for (auto p : particles)
	{
		p->update();
	}
}

void ParticleEmitter::render(SDL_Renderer* ren)
{
	if (!is_running)
		return;

	for (auto p : particles)
	{
		p->render(ren);
	}
}
