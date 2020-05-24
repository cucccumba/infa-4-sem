#pragma once

#include <SFML/Graphics.hpp>

struct apple
{
    apple(int x, int y, sf::Color Color):pos(x, y), color(Color)
    {}
    sf::Vector2i pos;
    sf::Color color;
    int i = 0;
};

class apple_container
{
public:
    std::vector<apple> &Get_apples();
private:
    std::vector<apple> apples;
};