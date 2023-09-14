#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "ECS.h"
#include "Game.h"

class Map : public Component
{
private:
    SDL_Texture *myMap[2];

public:
    Map()
    {
        myMap[0] = TextureManager::LoadTexture("assets/map0.png");
        myMap[1] = TextureManager::LoadTexture("assets/map1.png");
    }
    void render() override
    {
        TextureManager::RenderCopy(myMap[Game::state], 0, 0);
    }
};
