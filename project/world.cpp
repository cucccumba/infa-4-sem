#include "world.h"

World::World(int size)
:swarm(size), block_size(size)
{}

World::~World() = default;

void World::Spawn_Enemy(sf::Vector2u windowsize, int blocksize)
{
    int maxX = (windowsize.x / blocksize) - 2;
    int x = rand() % maxX + 1;
    int y = rand() % 4 + 1;
    swarm.Add(x, y);
}

void World::Spawn_Enemies(sf::Vector2u windowsize, int blocksize)
{
    int Max_Enemies = rand() % 4 + 1;
    for (int i = 0; i < Max_Enemies; ++i)
        Spawn_Enemy(windowsize, blocksize);
}

void World::Render(sf::RenderWindow &window)
{
    swarm.Render(window);
}

void World::Tick(sf::Vector2u windsize)
{
    swarm.Fire(windsize);
    swarm.Move(windsize);
}

int World::Kill_Enemy(Shooting &shooting)
{
    int killed = 0;
    killed += swarm.Kill(shooting.GetShootingC());
    killed += swarm.Kill(shooting.GetShootingL());
    killed += swarm.Kill(shooting.GetShootingR());
    return killed;
}

int World::GetBlockSize()
{
    return block_size;
}

void World::Check_hits_to_ship(Starship &ship)
{
    for (auto & shooting : swarm.Get_deleted_shootings())
    {
        for (auto it = shooting.GetShootingC().begin(); it < shooting.GetShootingC().end(); ++it)
        {
            if (ship.GetPosition() == (*it).position || (ship.GetPosition().x == (*it).position.x && ship.GetPosition().y - 1 == (*it).position.y))
            {
                ship.Decrease_Health();
                shooting.GetShootingC().erase(it);
            }
        }
    }
   for (auto & enemy : swarm.Get_Swarm())
   {
       for (auto it = enemy.shooting.GetShootingC().begin(); it < enemy.shooting.GetShootingC().end(); ++it)
       {
           if (ship.GetPosition() == (*it).position || (ship.GetPosition().x == (*it).position.x && ship.GetPosition().y - 1 == (*it).position.y))
           {
               ship.Decrease_Health();
               enemy.shooting.GetShootingC().erase(it);
           }
       }
       for (auto it = enemy.shooting.GetShootingL().begin(); it < enemy.shooting.GetShootingL().end(); ++it)
       {
           if (ship.GetPosition() == (*it).position || (ship.GetPosition().x == (*it).position.x && ship.GetPosition().y - 1 == (*it).position.y))
           {
               ship.Decrease_Health();
               enemy.shooting.GetShootingL().erase(it);
           }
       }
       for (auto it = enemy.shooting.GetShootingR().begin(); it < enemy.shooting.GetShootingR().end(); ++it)
       {
           if (ship.GetPosition() == (*it).position || (ship.GetPosition().x == (*it).position.x && ship.GetPosition().y - 1 == (*it).position.y))
           {
               ship.Decrease_Health();
               enemy.shooting.GetShootingR().erase(it);
           }
       }
   }
   if (ship.GetHealth() <= 0)
   {
       ship.Lose();
   }
}