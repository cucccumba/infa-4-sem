#pragma once

#include "window.h"
#include "enemy.h"
#include "starship.h"
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
    int KillEnemy();
    Window* GetWindow();

private:
    Window window;
    Starship ship;
    World world;
    TextBox textBox;
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time elapsed_Enemies_spawn;
    sf::Time elapsed_Enemies_move;
    sf::Texture space_texture;
};