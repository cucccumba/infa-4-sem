#pragma once

#include "window.h"
#include "snake.h"
#include "TextBox.h"
#include "apple.h"
#include <sstream>


class World
{
public:
    World(sf::Vector2u windsize);
    ~World();

    int GetBlockSize();
    void RespawnApple(sf::Vector2u windsize);
    apple_container& GetApples();
    void Update(Snake &player, std::vector<Snake> players, TextBox &textBox, sf::Vector2u windsize);
    void Render(sf::RenderWindow &window);

private:

    sf::Vector2u windowsize;
    sf::Vector2i item;
    int blocksize;
    //sf::Vector2i apple;
    //std::vector<apple> apples;
    apple_container appleContainer;
    sf::CircleShape appleshape;
    sf::RectangleShape bounds[4];
};