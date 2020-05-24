#include "snake.h"

Snake::Snake(int blocksize, int num, bool bot)
{
    size = blocksize;
    number = num;
    isbot = bot;
    bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
    Reset();
}

Snake::~Snake() {};

void Snake::Reset()
{
    snakebody.clear();
    if (number == 1)
    {
        snakebody.push_back(SnakeSegment(5, 7));
        snakebody.push_back(SnakeSegment(5, 6));
        snakebody.push_back(SnakeSegment(5, 5));
    }
    else if (number == 2)
    {
        snakebody.push_back(SnakeSegment(25, 7));
        snakebody.push_back(SnakeSegment(25, 6));
        snakebody.push_back(SnakeSegment(25, 5));
    }
    else if (number == 3)
    {
        snakebody.push_back(SnakeSegment(45, 7));
        snakebody.push_back(SnakeSegment(45, 6));
        snakebody.push_back(SnakeSegment(45, 5));
    }

    SetDirection(Direction::None);
    if (isbot)
        SetDirection(Direction::Right);
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

int Snake::GetNumber()
{
    return number;
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
}

void Snake::Tick(apple_container &apples)
{
    if (snakebody.empty())
        return;
    if (direction == Direction::None)
        return;
    Move(apples);
    CheckCollision();
}

void Snake::Move(apple_container &apples)
{
    for (int i = snakebody.size() - 1; i > 0; --i)
        snakebody[i].position = snakebody[i - 1].position;
    if (isbot)
    {
        if (!apples.Get_apples().empty())
        {
            int closest = 0;
            int closest_path = 0;
            sf::Vector2i head_pos = snakebody.front().position;
            for (int i = 0; i < apples.Get_apples().size(); ++i)
            {
                sf::Vector2i apple_pos = apples.Get_apples()[i].pos;
                if (i == 0)
                {
                    closest_path = abs(head_pos.x - apple_pos.x + head_pos.y - apple_pos.y);
                }
                else
                {
                    int path = abs(head_pos.x - apples.Get_apples()[i].pos.x + head_pos.y - apple_pos.y);
                    if (path < closest_path)
                    {
                        closest_path = path;
                        closest = i;
                    }
                }
            }
            if (apples.Get_apples()[closest].pos.x == snakebody[0].position.x)
            {
                if (apples.Get_apples()[closest].pos.y < snakebody[0].position.y)
                    direction = Direction::Up;
                else
                    direction = Direction::Down;
            }
            else if (apples.Get_apples()[closest].pos.y == snakebody[0].position.y)
            {
                if (apples.Get_apples()[closest].pos.x < snakebody[0].position.x)
                    direction = Direction::Left;
                else
                    direction = Direction::Right;
            }
            else
            {
                if (apples.Get_apples()[closest].pos.x < snakebody[0].position.x && apples.Get_apples()[closest].pos.y < snakebody[0].position.y && (direction == Direction::Down || direction == Direction::Right))
                {
                    if (direction == Direction::Down)
                        direction = Direction::Left;
                    else
                        direction = Direction::Up;
                }
                else if (apples.Get_apples()[closest].pos.x < snakebody[0].position.x && apples.Get_apples()[closest].pos.y > snakebody[0].position.y && (direction == Direction::Up || direction == Direction::Right))
                {
                    if (direction == Direction::Up)
                        direction = Direction::Left;
                    else
                        direction = Direction::Down;
                }
                else if (apples.Get_apples()[closest].pos.x > snakebody[0].position.x && apples.Get_apples()[closest].pos.y < snakebody[0].position.y && (direction == Direction::Down || direction == Direction::Left))
                {
                    if (direction == Direction::Down)
                        direction = Direction::Right;
                    else
                        direction = Direction::Up;
                }
                else if (apples.Get_apples()[closest].pos.x > snakebody[0].position.x && apples.Get_apples()[closest].pos.y > snakebody[0].position.y && (direction == Direction::Up || direction == Direction::Left))
                {
                    if (direction == Direction::Up)
                        direction = Direction::Right;
                    else
                        direction = Direction::Down;
                }
            }
        }
    }
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
    if (isbot)
        bodyRect.setFillColor(sf::Color::White);
    bodyRect.setPosition(head->position.x * size, head->position.y * size);
    window.draw(bodyRect);

    bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = snakebody.begin() + 1; itr != snakebody.end(); ++itr)
    {
        bodyRect.setPosition(itr->position.x * size, itr->position.y * size);
        window.draw(bodyRect);
    }
}

SnakeContainer Snake::GetSnakebody()
{
    return snakebody;
}