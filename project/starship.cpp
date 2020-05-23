#include "starship.h"

Starship::Starship(int blocksize, sf::Vector2u windsize)
: shooting(blocksize)
{
    size = blocksize;
    ShipShape.loadFromFile(R"(C:\Users\a-r-t\Pictures\Ship.png)");
    //ShipShape.setSize(sf::Vector2f(size, size));
    speed = 20;
    windowsize = windsize;
    direction = Direction::None;
    position = sf::Vector2i((windowsize.x / size) / 2, (windowsize.y / size) / 2);
    score = 0;
    lost = false;
    hp = 10;
}

Starship::~Starship() = default;

sf::Vector2i Starship::GetPosition()
{
    return position;
}

int Starship::GetSpeed()
{
    return speed;
}

int Starship::GetScore()
{
    return score;
}

void Starship::IncreaseScore(int x)
{
    score += x * 10;
}

Shooting& Starship::GetShooting()
{
    return shooting;
}

void Starship::SetDirection(Direction dir)
{
    direction = dir;
}

bool Starship::HasLost()
{
    return lost;
}

void Starship::Lose()
{
    lost = true;
}

int Starship::GetSize()
{
    return size;
}

Direction Starship::GetDirection()
{
    return direction;
}

sf::Vector2u Starship::GetWindowSize()
{
    return windowsize;
}

void Starship::Tick()
{
    Fire();
    if (direction == Direction::None)
        return;
    Move();
}

void Starship::Move()
{
    if (direction == Direction::Left)
    {
        --position.x;
    }
    else if (direction == Direction::Right)
    {
        ++position.x;
    }
    else if (direction == Direction::Up)
    {
        --position.y;
    }
    else if (direction == Direction::Down)
    {
        ++position.y;
    }
}

void Starship::Render(sf::RenderWindow &window)
{
    sf::Sprite ShipSprite(ShipShape);
    sf::Vector2u s_size = ShipShape.getSize();
    ShipSprite.setOrigin(s_size.x / 2 - 8, s_size.y / 2);
    ShipSprite.setPosition(position.x * size, position.y * size);
    //ShipShape.setFillColor(sf::Color::Red);
    window.draw(ShipSprite);
    shooting.Render(window);
}

void Starship::Fire()
{
    shooting.Add(position.x, position.y, false);
    shooting.Move(windowsize, false);
}

void Starship::Decrease_Health()
{
    --hp;
}

int Starship::GetHealth()
{
    return hp;
}