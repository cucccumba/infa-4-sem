#pragma once

#include "window.h"
#include "ammo.h"

enum class Direction
{
    None,
    Up,
    Down,
    Left,
    Right
};

class Starship
{
public:
    Starship (int blocksize, sf::Vector2u windsize);
    ~Starship();

    int GetSpeed();
    void SetDirection(Direction dir);
    Direction GetDirection();
    sf::Vector2i GetPosition();
    int GetScore();
    void IncreaseScore(int x);
    bool HasLost();
    void Lose();
    void Tick();
    void Move();
    void Render(sf::RenderWindow &window);
    int GetSize();
    void Fire();
    sf::Vector2u GetWindowSize();
    Shooting &GetShooting();
    void Decrease_Health();
    int GetHealth();

private:
    int size;
    Direction direction;
    Shooting shooting;
    int score;
    int speed;
    bool lost;
    int hp;
    sf::Vector2i position;
    sf::Vector2u windowsize;
    //sf::RectangleShape ShipShape;
    sf::Texture ShipShape;
};
