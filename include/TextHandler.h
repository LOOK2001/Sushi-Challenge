//Class for handling text creation
#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_ttf.h>
#include <iostream>

class TextHandler
{
    public:

    TextHandler();

    //Initialize text with path to font, starting position, color, and size
    void text_init(SDL_Renderer* renderer, const char* fpath, int x_start, int y_start, SDL_Color start_color, int size);

    //Update text with string that will be displayed
    void text_update(const char* charString);

    //Render our text as an image
    void text_render(SDL_Rect pause_rect);

    private:

    SDL_Renderer* text_renderer;
    TTF_Font* text_font;
    SDL_Rect text_rect;
    SDL_Texture* text_texture;

    int x_pos;
    int y_pos;
    SDL_Color color;
};

#endif