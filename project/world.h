#pragma once

#include "window.h"

class World
{
public:
    World(sf::Vector2u windsize);
    ~World();

    void Update();
    void Render(sf::RenderWindow &window);

private:
    sf::Vector2u windowsize;
    // textures ...
};