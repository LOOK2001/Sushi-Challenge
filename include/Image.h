// class that manipulates image data and accesses filds such as the image's width and height
#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Image {
public:
	Image(const char *name);
	Image(SDL_Surface* surf, int _x = 0, int _y = 0, int _w = 0, int _h = 0);
	virtual ~Image();
	Image& operator=(const Image& _image);

	void load_image(const char* name);

	void Draw(SDL_Rect dest) {}
	virtual void Draw(float _x, float _y, double angle, const SDL_FPoint* center, const SDL_RendererFlip flip = SDL_FLIP_NONE, float scale = 1) const;
	virtual void Draw(float x, float y, float scale= 1) const;

	//virtual void ScaleInPlace(float scale= 1);

	int GetImgWidth() const { return surface->w; }
	int GetImagHeight() const { return surface->h; }
	SDL_Surface* GetSurface() const { return surface; }

	void SetView(int _x, int _y, int _w, int _h) { view = { _x, _y, _w, _h }; }
	void SetViewPos(int _x, int _y) { view.x = _x, view.y = _y; }
	void SetViewSize(int& w, int& h) { w = view.w, h = view.h; }
	int GetViewWidth() const { return view.w; }
	int GetViewHeight() const { return view.h; }

	SDL_Texture* GetTexture() { return texture; }

protected:
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect view;
	//int dest_w = view.w;
	//int dest_h = view.h;
};

#endif //IMAGE_H
