#pragma once

#include "enemy.h"
#include "starship.h"

class World
{
public:
    World(int size);
    ~World();

    void Spawn_Enemy(sf::Vector2u windowsize, int blocksize);
    void Spawn_Enemies(sf::Vector2u windowsize, int blocksize);
    void Render(sf::RenderWindow &window);
    void Tick(sf::Vector2u windsize);
    int Kill_Enemy(Shooting &shooting);
    void Check_hits_to_ship(Starship &ship);
    int GetBlockSize();
private:
    Swarm swarm;
    int block_size;
};