#pragma once

#include "window.h"
#include "snake.h"
class World
{
public:
    World(sf::Vector2u windsize);
    ~World();

    int GetBlockSize();
    void RespawnApple();
    sf::Vector2i GetApple();
    void Update(Snake &player, std::vector<Snake> players);
    void Render(sf::RenderWindow &window);

private:
    sf::Vector2u windowsize;
    sf::Vector2i item;
    int blocksize;
    sf::Vector2i apple;
    sf::CircleShape appleshape;
    sf::RectangleShape bounds[4];
};