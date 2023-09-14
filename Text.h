#pragma once

#include "SDL.h"
#include <string>
#include "TextureManager.h"

class Text
{
private:
    SDL_Texture *number, *character;
    int len;
    SDL_Rect src, dst;
    std::string str;

public:
    Text()
    {
        number = TextureManager::LoadTexture("assets/number.png");
        character = TextureManager::LoadTexture("assets/character.png");
    }
    void DrawText(std::string text, SDL_Rect d)
    {
        len = 0;
        for (int i = 0; i < text.size(); i++) len += ((text[i] == ' ') ? 30 : 60);
        len -= 10;

        src.x = 0; src.y = 0;
        src.w = 50; src.h = 87;

        dst.x = d.x; dst.y = d.y;
        dst.w = 50.0 * double(d.w) / double(len);
        dst.h = d.h;

        for (int i = 0; i < text.size(); i++) {
            if (text[i] >= 'A' && text[i] <= 'Z') text[i] -= ('A' - 'a');
            if (text[i] >= 'a' && text[i] <= 'z') {
                src.x = (text[i] - 'a') * 50;
                TextureManager::RenderCopy(character, &src, &dst);
                dst.x += 60.0 * double(d.w) / double(len);
            }
            else if (text[i] >= '0' && text[i] <= '9') {
                src.x = (text[i] - '0') * 50;
                TextureManager::RenderCopy(number, &src, &dst);
                dst.x += 60.0 * double(d.w) / double(len);
            }
            else dst.x += 30.0 * double(d.w) / double(len);
        }
    }
    void DrawNumber(int u, SDL_Rect d)
    {
        if (u == 0) str = "0";
        else {
            str = "";
            while (u) {
                str = char(u % 10 + '0') + str;
                u /= 10;
            }
        }
        DrawText(str, d);
    }
};
