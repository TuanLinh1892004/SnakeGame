#pragma once

#include "TextureManager.h"
#include "ECS.h"
#include "Game.h"
#include "SDL.h"

class Snake : public Component
{
private:
    int x, y, curx, cury;
    double speed, v;
    int direction, newdir;
    int length, curlen;
    SDL_Texture *head, *body, *tail;
    int a[20][20];
    SDL_Rect dst;
    bool changed;

public:
    Snake()
    {
        head = TextureManager::LoadTexture("assets/head.png");
        body = TextureManager::LoadTexture("assets/body.png");
        tail = TextureManager::LoadTexture("assets/tail.png");
    }

    void setSpeed(double u) { speed = u; speed = 380 - speed;}
    void setLength() { length++; }
    void init() override
    {
        x = y = 10;
        direction = 0;
        length = 2;
        for (int i = 0; i < 20; i++) for (int j = 0; j < 20; j++) a[i][j] = -1;
        a[10][10] = 0;
        a[9][10] = 0;
        v = 0; changed = 0;
    }
    bool check(int x, int y) { return (a[x][y] != -1); }
    void update() override
    {
        if (!Game::state) return;
        Game::score = length - 2;
        if (Game::max_score < length - 2) Game::max_score = length - 2;
        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_RIGHT && direction != 2) newdir = 0;
            if (Game::event.key.keysym.sym == SDLK_DOWN  && direction != 3) newdir = 1;
            if (Game::event.key.keysym.sym == SDLK_LEFT  && direction != 0) newdir = 2;
            if (Game::event.key.keysym.sym == SDLK_UP    && direction != 1) newdir = 3;
            if (direction != newdir) changed = 1;
            direction = newdir;
        }
        v += 2.2;
        if (v >= speed || changed) {
            curx = x; cury = y;
            if      (direction == 0) x++;
            else if (direction == 1) y++;
            else if (direction == 2) x--;
            else                     y--;
            v = 0; changed = 0;
            if (x < 0) x = 19;
            if (x > 19) x = 0;
            if (y < 0) y = 19;
            if (y > 19) y = 0;
            if (a[x][y] != -1) {
                SDL_Delay(500);
                this->init();
                Game::state = 0;
                return;
            }
            a[x][y] = direction;
        }

    }
    void render() override
    {
        if (!Game::state) return;
        curx = x; cury = y;
        curlen = 0;
        while (1) {
            curlen++;
            dst.x = curx * 25 + 2; dst.y = cury * 25 + 120 + 2; dst.w = dst.h = 25 - 4;
            if (curlen == 1)           TextureManager::RenderCopyEx(head, 0, &dst, 90 * a[curx][cury], 0, SDL_FLIP_NONE);
            else if (curlen == length) TextureManager::RenderCopyEx(tail, 0, &dst, 90 * a[curx][cury], 0, SDL_FLIP_NONE);
            else                       TextureManager::RenderCopyEx(body, 0, &dst, 90 * a[curx][cury], 0, SDL_FLIP_NONE);
            if      (a[curx][cury] == 0) curx--;
            else if (a[curx][cury] == 1) cury--;
            else if (a[curx][cury] == 2) curx++;
            else                         cury++;
            if (curx < 0) curx = 19;
            if (curx > 19) curx = 0;
            if (cury < 0) cury = 19;
            if (cury > 19) cury = 0;
            if (curlen == length) {
                a[curx][cury] = -1;
                break;
            }
        }
    }
};
