#include "include/Particle.h"
#include "include/Global.h"

void Particle::init(const char* graphics, SDL_Renderer* ren, int start_x, int start_y, int width, int height)
{
	img = new Image(graphics);

	SetPosition(start_x, start_y);
	setSize(width, height);
}

void Particle::update()
{
	translate(x_vel, y_vel);

	// 100 pixels meter
	//y_vel += 9.8 * 100.0 / 3600.0;

	if (lifetime > 0)
	{
		rect.w = (int)rect.w / 2 + rect.w * (int)(10 * lifetime / 100);
		rect.h = (int)rect.h / 2 + rect.h * (int)(10 * lifetime / 100);
	}

	lifetime--;
}

void Particle::render(SDL_Renderer* ren)
{
	if (lifetime > 0)
	{
		SDL_SetTextureAlphaMod(img->GetTexture(), (int)255 * lifetime / 20.0);
		img->Draw(rect.x, rect.y);
	}else {
		SDL_SetTextureAlphaMod(img->GetTexture(), 255);
	}
}