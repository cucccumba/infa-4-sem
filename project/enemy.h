#pragma once

#include "window.h"
#include "ammo.h"

struct Enemy
{
    Enemy(int x, int y, int size) : position(x, y), shooting(size){}
    sf::Vector2i position;
    Shooting shooting;
};

using EnemyContainer = std::vector<Enemy>;

class Swarm
{
public:
    Swarm(int Size);
    ~Swarm();

    void Add(int x, int y);
    void Move(sf::Vector2u windsize);
    void Fire(sf::Vector2u windsize);
    void Render(sf::RenderWindow &window);
    int Kill(AmmoContainer& shooting);
    std::vector<Shooting> &Get_deleted_shootings();
    EnemyContainer &Get_Swarm();
private:
    int size;
    EnemyContainer swarm;
    std::vector<Shooting> deleted_shootings;
    //sf::RectangleShape Enemyshape;
    sf::Texture enemy_shape;
};