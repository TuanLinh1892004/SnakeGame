#pragma once

#include "SDL.h"
#include "ECS.h"
#include "TextureManager.h"
#include "Game.h"

class Button : public Component
{
private:
    SDL_Texture *texture;
    SDL_Rect dst;

public:
    Button()
    {
        texture = TextureManager::LoadTexture("assets/button.png");
        dst.x = 225; dst.y = 550;
        dst.w = 50; dst.h = 50;
    }
    void update() override
    {
        if (Game::state) return;
        if (Game::event.type == SDL_MOUSEBUTTONUP)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= dst.x && x <= dst.x + dst.w && y >= dst.y && y <= dst.y + dst.h) Game::state = 1;
        }
    }
    void render() override
    {
        if (!Game::state) TextureManager::RenderCopy(texture, 0, &dst);
    }
};
