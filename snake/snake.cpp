#include "snake.h"

Snake::Snake(int blocksize)
{
    size = blocksize;
    bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
    Reset();
}

Snake::~Snake() {};

void Snake::Reset()
{
    snakebody.clear();
    snakebody.push_back(SnakeSegment(5, 7));
    snakebody.push_back(SnakeSegment(5, 6));
    snakebody.push_back(SnakeSegment(5, 5));

    SetDirection(Direction::None);
    speed = 20;
    score = 0;
    lost = false;
}

void Snake::SetDirection(Direction dir)
{
    direction = dir;
}

Direction Snake::GetDirection()
{
    return direction;
}

int Snake::GetSpeed()
{
    return speed;
}

sf::Vector2i Snake::GetPosition()
{
    return (!snakebody.empty() ? snakebody.front().position : sf::Vector2i(1, 1));
}

int Snake::GetScore()
{
    return score;
}

void Snake::IncreaseScore()
{
    score += 10;
}

bool Snake::HasLost()
{
    return lost;
}

void Snake::Lose()
{
    lost = true;
}

void Snake::ToggleLost()
{
    lost = !lost;
}

void Snake::Extend()
{
    if (snakebody.empty())
        return;
    SnakeSegment &tail_head = snakebody[snakebody.size() - 1];
    if (snakebody.size() > 1)
    {
        SnakeSegment &tail_bone = snakebody[snakebody.size() - 2];
        if (tail_head.position.x == tail_bone.position.x)
        {
            if (tail_head.position.y > tail_bone.position.y)
                snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
            else
                snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
        }
        else if (tail_head.position.y == tail_bone.position.y)
        {
            if (tail_head.position.x > tail_bone.position.x)
                snakebody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
            else
                snakebody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
        }
    }
    else
    {
        if(direction == Direction::Up)
        {
            snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
        }
        else if (direction == Direction::Down)
        {
            snakebody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
        }
        else if (direction == Direction::Left)
        {
            snakebody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
        }
        else if (direction == Direction::Right)
        {
            snakebody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
        }
    }
    speed += 1;
}

void Snake::Tick()
{
    if (snakebody.empty())
        return;
    if (direction == Direction::None)
        return;
    Move();
    CheckCollision();
}

void Snake::Move()
{
    for (int i = snakebody.size() - 1; i > 0; --i)
        snakebody[i].position = snakebody[i - 1].position;
    if (direction == Direction::Left)
    {
        --snakebody[0].position.x;
    }
    else if (direction == Direction::Right)
    {
        ++snakebody[0].position.x;
    }
    else if (direction == Direction::Up)
    {
        --snakebody[0].position.y;
    }
    else if (direction == Direction::Down)
    {
        ++snakebody[0].position.y;
    }
}

void Snake::CheckCollision()
{
    if (snakebody.size() < 5)
        return;
    SnakeSegment &head = snakebody.front();
    for (auto itr = snakebody.begin() + 1; itr != snakebody.end(); ++itr)
    {
        if (itr->position == head.position)
        {
            Lose();
            break;
        }
    }
}

void Snake::Render(sf::RenderWindow &window)
{
    if (snakebody.empty())
        return;
    auto head = snakebody.begin();
    bodyRect.setFillColor(sf::Color::Yellow);
    bodyRect.setPosition(head->position.x * size, head->position.y * size);
    window.draw(bodyRect);

    bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = snakebody.begin() + 1; itr != snakebody.end(); ++itr)
    {
        bodyRect.setPosition(itr->position.x * size, itr->position.y * size);
        window.draw(bodyRect);
    }
}