#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include "Particle.h"


#define MAX_PARTS 10

class ParticleEmitter : public GameObject {

public:
	ParticleEmitter() {};
	~ParticleEmitter() 
	{
		for (auto p : particles)
		{
			if (p)
				delete p;
		}
	};

	void init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int type);

	virtual void update();
	virtual void render(SDL_Renderer* ren);
	virtual void quit() {};

	void Start() { is_running = true; }
	void SetRunning(bool _run) { is_running = _run; }

private:
	std::vector<Particle*> particles;
	int pos_x;
	int pos_y;
	int part_type;
	bool is_running;
};

#endif // PARTICLE_EMITTER_H