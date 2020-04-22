#pragma once

#include "window.h"

struct Ammo
{
    Ammo(int x, int y) : position(x, y){}
    sf::Vector2i position;
};

using AmmoContainer = std::vector<Ammo>;

class Shooting
{
public:
    Shooting(int size);
    ~Shooting();
    void Move(sf::Vector2u windsize);
    void Add(int x, int y);
    void Render(sf::RenderWindow &window);
    AmmoContainer* GetShootingC();
    AmmoContainer* GetShootingL();
    AmmoContainer* GetShootingR();
private:
    AmmoContainer shootingC;
    AmmoContainer shootingL;
    AmmoContainer shootingR;
    int size;
    sf::RectangleShape shootShape;
};
