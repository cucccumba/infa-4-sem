#pragma once

#include "window.h"

struct Ammo
{
    Ammo(int x, int y, int Type) : position(x, y), type(Type){}
    sf::Vector2i position;
    int type;
};

using AmmoContainer = std::vector<Ammo>;

class Shooting
{
public:
    Shooting(int size);
    ~Shooting();
    void Move(sf::Vector2u windsize, bool is_enemy);
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
