#pragma once

#include "window.h"
#include "starship.h"
class World
{
public:
    World(sf::Vector2u windsize);
    ~World();

    int GetBlockSize();
    void Update();
    void Render(sf::RenderWindow &window);

private:
    sf::Vector2u windowsize;
    int blocksize;

};