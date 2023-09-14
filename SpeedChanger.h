#pragma once

#include "SDL.h"
#include "Game.h"
#include "TextureManager.h"
#include "ECS.h"

class SpeedChanger : public Component
{
private:
    SDL_Texture *black, *red, *blue, *circle;
    SDL_Rect dst;
    double speed;
    bool ok;
    int x, y;

public:
    SpeedChanger()
    {
        red = TextureManager::LoadTexture("assets/red.png");
        blue = TextureManager::LoadTexture("assets/blue.png");
        black = TextureManager::LoadTexture("assets/black.png");
        circle = TextureManager::LoadTexture("assets/circle.png");
        speed = 0;
        ok = 0;
    }

    double getSpeed() { return speed; }

    void update() override
    {
        if (Game::state) return;
        if (!ok && Game::event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&x, &y);
            if (x >= 100 && x <= 400 && y >= 485 && y <= 525) ok = 1;
        }
        if (Game::event.type == SDL_MOUSEBUTTONUP) ok = 0;

        if (ok)
        {
            SDL_GetMouseState(&x, &y);
            speed = x - 100;
            if (speed < 0) speed = 0;
            if (speed > 300) speed = 300;
        }
    }
    void render() override
    {
        if (Game::state) return;
        dst.x = 95; dst.y = 495; dst.w = 310; dst.h = 20;
        TextureManager::RenderCopy(black, 0, &dst);
        dst.x = 100; dst.y = 500; dst.w = 300; dst.h = 10;
        TextureManager::RenderCopy(red, 0, &dst);
        dst.w = speed;
        TextureManager::RenderCopy(blue, 0, &dst);
        dst.x = speed + 80; dst.y = 485; dst.w = 40; dst.h = 40;
        TextureManager::RenderCopy(circle, 0, &dst);
        dst.x = 150; dst.y = 455; dst.w = 200; dst.h = 25;
        Game::printText->DrawText("choose speed", dst);
    }
};
