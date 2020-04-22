#pragma once

#include "window.h"
#include "world.h"
#include "enemy.h"
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
    sf::Time elapsed;
    sf::Time elapsedEnemies;
};