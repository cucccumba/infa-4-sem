#pragma once

#include "window.h"

enum class Direction
{
    None,
    Up,
    Down,
    Left,
    Right
};

struct SnakeSegment
{
    SnakeSegment (int x, int y) : position(x, y) {};
    sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

class Snake
{
public:
    Snake (int blocksize);
    ~Snake();

    void SetDirection(Direction dir);
    Direction GetDirection();
    int GetSpeed();
    sf::Vector2i GetPosition();
    int GetScore();
    void IncreaseScore();
    bool HasLost();
    void Lose();
    void ToggleLost();
    void Extend();
    void Reset();
    void Move();
    void Tick();
    void Render(sf::RenderWindow &window);

private:
    void CheckCollision();
    SnakeContainer snakebody;
    int size;
    Direction direction;
    int speed;
    int score;
    bool lost;
    sf::RectangleShape bodyRect;
};