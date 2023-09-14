#pragma once

#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char *filename)
    {
        SDL_Surface *surface = IMG_Load(filename);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }
    static void RenderCopy(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst)
    {
        SDL_RenderCopy(Game::renderer, texture, src, dst);
    }
    static void RenderCopyEx(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst, double angle, SDL_Point *center, SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx(Game::renderer, texture, src, dst, angle, center, flip);
    }
};
