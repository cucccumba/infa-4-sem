#pragma once

#include "window.h"
#include "world.h"
#include "TextBox.h"
class Game
{
public:
    Game();
    ~Game();

    void Restartclock();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();

private:
    World world;
    TextBox textBox;
    std::vector<Snake> players;
    Window window;
    sf::Clock clock;
    sf::Time elapsed;
};