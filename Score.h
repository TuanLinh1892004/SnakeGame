#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "Game.h"
#include "ECS.h"
#include "Text.h"

class Score : public Component
{
private:
    SDL_Rect dst;
    int cnt;

public:
    Score() = default;

    int digit(int u)
    {
        if (u == 0) return 1;
        cnt = 0;
        while (u) {
            cnt++;
            u /= 10;
        }
        return cnt;
    }
    void render() override
    {
        if (Game::state == 0) {
            dst.x = 100; dst.y = 200; dst.w = 150; dst.h = 60;
            Game::printText->DrawText("score", dst);
            dst.x = 300; dst.w = digit(Game::score) * 40;
            Game::printText->DrawNumber(Game::score, dst);
            dst.x = 20; dst.y = 300; dst.w = 230; dst.h = 60;
            Game::printText->DrawText("max score", dst);
            dst.x = 300; dst.w = digit(Game::max_score) * 40;
            Game::printText->DrawNumber(Game::max_score, dst);
        }
        else {
            dst.x = 100; dst.y = 30; dst.w = 150; dst.h = 60;
            Game::printText->DrawText("score", dst);
            dst.x = 300; dst.w = digit(Game::score) * 40;
            Game::printText->DrawNumber(Game::score, dst);
        }
    }
};
