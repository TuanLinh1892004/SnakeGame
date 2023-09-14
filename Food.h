#pragma once

#include "SDL.h"
#include "ECS.h"
#include "TextureManager.h"
#include "Game.h"

class Food : public Component
{
private:
    int x, y;
    SDL_Texture *texture;
    SDL_Rect dst;

public:
    Food()
    {
        texture = TextureManager::LoadTexture("assets/food.png");
    }
    int X() { return x; }
    int Y() { return y; }
    void change()
    {
        x = rand() % 20; y = rand() % 20;
    }
    void init() override
    {
        change();
    }
    void render() override
    {
        if (!Game::state) return;
        dst.x = x * 25 + 2; dst.y = y * 25 + 120 + 2; dst.w = dst.h = 25 - 4;
        TextureManager::RenderCopy(texture, 0, &dst);
    }
};
