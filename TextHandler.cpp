#include "include/TextHandler.h"

TextHandler::TextHandler()
{
    text_renderer = NULL;
    text_font = NULL;
    text_texture = NULL;

    x_pos = 0;
    y_pos = 0;
}

void TextHandler::text_init(SDL_Renderer* renderer, const char* fpath, int x_start, int y_start, SDL_Color color_start, int size)
{
    if(TTF_Init() == -1)
    {
        std::cout << "Could not initialize ttf library." << std::endl;
    }
    text_renderer = renderer;

    text_font = TTF_OpenFont(fpath, size);
    if(!text_font)
    {
        std::cout << "Font not loaded." << std::endl;
    }

    x_pos = x_start;
    y_pos = y_start;

    text_rect.x = x_pos;
    text_rect.y = y_pos;

    color = color_start;
}

void TextHandler::text_update(const char* charString)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(text_font, charString, color);
    if(!(text_surface))
    {
        std::cout << "Font not loaded. Could not create surface." << std::endl;
    }
    else
    {
        text_texture = SDL_CreateTextureFromSurface(text_renderer, text_surface);
        SDL_FreeSurface(text_surface);

        int w;
        int h;
        SDL_QueryTexture(text_texture, NULL, NULL, &w, &h);

        text_rect.w = w;
        text_rect.h = h;

        text_rect.x = x_pos - (w/2);
        text_rect.y = y_pos - (h/2);
    }
}

void TextHandler::text_render(SDL_Rect pause_rect)
{
    SDL_RenderCopy(text_renderer, text_texture, NULL, &text_rect);
}