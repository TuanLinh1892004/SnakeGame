#include "Game.h"
#include "ECS.h"
#include "Button.h"
#include "Map.h"
#include "Score.h"
#include "Text.h"
#include "SpeedChanger.h"
#include "Snake.h"
#include "Food.h"

Manager manager;
auto &myMap(manager.addEntity());
auto &button(manager.addEntity());
auto &myScore(manager.addEntity());
auto &speedChanger(manager.addEntity());
auto &food(manager.addEntity());
auto &snake(manager.addEntity());

SDL_Renderer *Game::renderer;
SDL_Event Game::event;
Text *Game::printText;
int Game::state = 0, Game::score = 0, Game::max_score = 0;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int x, int y, int w, int h, int flag)
{
    window = SDL_CreateWindow(title, x, y, w, h, flag);
    Game::renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    running = 1;
    Game::printText = new Text();

    myMap.addComponent <Map>();
    button.addComponent <Button>();
    myScore.addComponent <Score>();
    speedChanger.addComponent <SpeedChanger>();
    food.addComponent <Food>();
    snake.addComponent <Snake>();
}

void Game::handleEvents()
{
    SDL_PollEvent(&Game::event);
    if (Game::event.type == SDL_QUIT) running = 0;
}

void Game::update()
{
    manager.refresh();
    manager.update();
    if (Game::state == 0) snake.getComponent <Snake>().setSpeed(speedChanger.getComponent <SpeedChanger>().getSpeed());
    else if (snake.getComponent <Snake>().check(food.getComponent <Food>().X(), food.getComponent <Food>().Y())) {
        snake.getComponent <Snake>().setLength();
        food.getComponent <Food>().change();
    }
}

void Game::render()
{
    SDL_RenderClear(Game::renderer);
    manager.render();
    SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    IMG_Quit();
    SDL_Quit();
}
