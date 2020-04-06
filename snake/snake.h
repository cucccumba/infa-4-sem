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
    Snake (int blocksize, int num, bool bot);
    ~Snake();

    void SetDirection(Direction dir);
    Direction GetDirection();
    int GetSpeed();
    sf::Vector2i GetPosition();
    int GetScore();
    int GetNumber();
    SnakeContainer GetSnakebody();
    void IncreaseScore();
    bool HasLost();
    void Lose();
    void ToggleLost();
    void Extend();
    void Reset();
    void Move(sf::Vector2i apple);
    void Tick(sf::Vector2i apple);
    void Render(sf::RenderWindow &window);

private:
    void CheckCollision();
    SnakeContainer snakebody;
    int size;
    Direction direction;
    int speed;
    int score;
    bool lost;
    bool isbot;
    int number;
    sf::RectangleShape bodyRect;
};