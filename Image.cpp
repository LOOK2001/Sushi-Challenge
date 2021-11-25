
#include "include/Image.h"
#include "include/Camera.h"
#include "include/Global.h"

Image::Image(const char *name)
{
	renderer = nullptr;
	surface = nullptr;
	texture = nullptr;

	renderer = Global::GetRenderer();
	load_image(name);
}

Image::Image(SDL_Surface* surf, int _x /*= 0*/, int _y /*= 0*/, int _w, int _h)
{
	renderer = nullptr;
	surface = nullptr;
	texture = nullptr;

	renderer = Global::GetRenderer();

	if (surface)
		SDL_FreeSurface(surface);

	if (texture)
		SDL_DestroyTexture(texture);

	surface = surf;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	view = { _x, _y, _w, _h };
}

Image::~Image()
{
	if (surface)
		SDL_FreeSurface(surface);

	if (texture)
		SDL_DestroyTexture(texture);
}

Image& Image::operator=(const Image& _image)
{
	texture = _image.texture;
	return *this;
}

void Image::load_image(const char* name)
{
	if (surface)
		SDL_FreeSurface(surface);

	if (texture)
		SDL_DestroyTexture(texture);

	surface = IMG_Load(name);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	view = { 0, 0, surface->w, surface->h };
}

void Image::Draw(float _x, float _y, float scale) const
{
	Camera* camera = Global::GetMainCamera();
	SDL_FPoint pos = camera->GetPos();

	float x = _x - pos.x;
	float y = _y - pos.y;

	//SDL_FRect dest = { (float)x, (float)y, view.w * scale, view.h * scale };
	//SDL_RenderCopyF(renderer, texture, &view, &dest);

	if (camera->IsInsideView(x, y))
	{
		SDL_FRect dest = { (float)x, (float)y, view.w * scale, view.h * scale };
		SDL_RenderCopyF(renderer, texture, &view, &dest);
	}
}

void Image::Draw(float _x, float _y, double angle, const SDL_FPoint* _center, const SDL_RendererFlip flip /*= SDL_FLIP_NONE*/, float scale /*= 1*/) const
{
	Camera* camera = Global::GetMainCamera();
	SDL_FPoint pos = camera->GetPos();

	float x = _x * scale - pos.x;
	float y = _y * scale - pos.y;

	SDL_FRect dest = { (float)x, (float)y, view.w * scale, view.h * scale };
	SDL_RenderCopyExF(renderer, texture, &view, &dest,
		angle, _center, flip);
}
