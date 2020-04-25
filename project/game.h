#pragma once

#include "window.h"
#include "enemy.h"
#include "starship.h"
class Game
{
public:
    Game();
    ~Game();

    void Restartclock();

    void HandleInput();
    void Update();
    void Render();
    void KillEnemy();
    Window* GetWindow();

private:
    Starship ship;
    Swarm swarm;
    Window window;
    sf::Clock clock;
    sf::Clock enemies;
    sf::Clock enemies_move;
    sf::Time elapsed;
    sf::Time elapsed_Enemies_spawn;
    sf::Time elapsed_Enemies_move;
};