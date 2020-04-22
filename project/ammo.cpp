#include "ammo.h"

Shooting::Shooting(int Size)
{
    size = Size;
    shootShape.setFillColor(sf::Color::Yellow);
    shootShape.setSize(sf::Vector2f(size / 6, size / 2));
}

Shooting::~Shooting() = default;

void Shooting::Add(int x, int y)
{
    shootingC.push_back(Ammo(x, y));
    shootingL.push_back(Ammo(x, y));
    shootingR.push_back(Ammo(x, y));
}

void Shooting::Move(sf::Vector2u windsize)
{
    for (auto & shoot : shootingC)
        shoot.position.y -= 2;
    for (auto & shoot : shootingL)
    {
        shoot.position.y -= 2;
        shoot.position.x -= 1;
    }
    for (auto & shoot : shootingR)
    {
        shoot.position.y -= 2;
        shoot.position.x += 1;
    }

    for (auto itr = shootingC.begin(); itr < shootingC.end(); ++itr)
    {
        if ((*itr).position.y < 0)
            shootingC.erase(itr);
    }
    for (auto itr = shootingL.begin(); itr < shootingL.end(); ++itr)
    {
        if ((*itr).position.y < 0 || (*itr).position.x < 0)
            shootingL.erase(itr);
    }
    for (auto itr = shootingR.begin(); itr < shootingR.end(); ++itr)
    {
        if ((*itr).position.y < 0 || (*itr).position.x > windsize.x / size)
            shootingR.erase(itr);
    }
}

void Shooting::Render(sf::RenderWindow &window)
{
    for (const auto & shoot : shootingC)
    {
        shootShape.setPosition(shoot.position.x * size + size / 2, shoot.position.y * size);
        window.draw(shootShape);
    }
    for (const auto & shoot : shootingL)
    {
        shootShape.setPosition(shoot.position.x * size + size / 2, shoot.position.y * size);
        window.draw(shootShape);
    }
    for (const auto & shoot : shootingR)
    {
        shootShape.setPosition(shoot.position.x * size + size / 2, shoot.position.y * size);
        window.draw(shootShape);
    }
}

AmmoContainer* Shooting::GetShootingC()
{
    return &shootingC;
}

AmmoContainer* Shooting::GetShootingL()
{
    return &shootingL;
}

AmmoContainer* Shooting::GetShootingR()
{
    return &shootingR;
}