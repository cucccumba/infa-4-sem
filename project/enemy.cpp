#include "enemy.h"
#include "algorithm"

Swarm::Swarm(int Size)
{
    size = Size;
    Enemyshape.setFillColor(sf::Color::Blue);
    Enemyshape.setSize(sf::Vector2f(size, size));
}

Swarm::~Swarm()= default;

void Swarm::Add(int x, int y)
{
    swarm.push_back(Enemy(x, y));
}

void Swarm::Move(sf::Vector2u windsize)
{
    if (swarm.empty())
        return;
    for (auto & s : swarm)
        ++s.position.y;
    for (auto itr = swarm.begin(); itr < swarm.end(); ++itr)
    {
        if ((*itr).position.y > (windsize.y / size))
            swarm.erase(itr);
    }
}

void Swarm::Kill(AmmoContainer* shooting)
{
    if (shooting->empty())
        return;
   for (auto itr1 = (*shooting).begin(); itr1 < (*shooting).end(); ++itr1)
   {
       for (auto itr = swarm.begin(); itr < swarm.end(); ++itr)
       {
           if ((*itr1).position == (*itr).position)
           {
               swarm.erase(itr);
               (*shooting).erase(itr1);
           }
       }
   }
}

void Swarm::Render(sf::RenderWindow &window)
{
    for (auto enemy : swarm)
    {
        Enemyshape.setPosition(enemy.position.x * size, enemy.position.y * size);
        window.draw(Enemyshape);
    }
}
