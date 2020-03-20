#pragma once

#include "window.h"
class Game
{
public:
    Game();
    ~Game();

    sf::Time GetElapsed();
    void Restartclock();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();

private:
    void MoveMushroom();
    Window window;
    sf::Clock clock;
    sf::Time elapsed;
    sf::Texture mashroomTexture;
    sf::Sprite mashroom;
    sf::Vector2i increment;
    //textures ...
};