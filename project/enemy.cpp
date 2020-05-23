#include "enemy.h"
#include "algorithm"

Swarm::Swarm(int Size)
{
    size = Size;
    //Enemyshape.setFillColor(sf::Color::Blue);
    //Enemyshape.setSize(sf::Vector2f(size, size));
    enemy_shape.loadFromFile(R"(C:\Users\a-r-t\Pictures\enemy.png)");
}

Swarm::~Swarm()
{
    swarm.clear();
}

void Swarm::Add(int x, int y)
{
    swarm.push_back(Enemy(x, y, size));
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

int Swarm::Kill(AmmoContainer& shooting)
{
    int count_killed = 0;
    if (shooting.empty())
        return 0;
   for (auto itr1 = (shooting).begin(); itr1 < (shooting).end(); ++itr1)
   {
       for (auto itr = swarm.begin(); itr < swarm.end(); ++itr)
       {
           if (((*itr1).position == (*itr).position ) || (((*itr1).position.y + 1 == (*itr).position.y) && (*itr1).position.x == (*itr).position.x))
           {
               deleted_shootings.push_back((*itr).shooting);
               swarm.erase(itr);
               (shooting).erase(itr1);
               ++count_killed;
           }
           if ((*itr1).type == -1)  //left fire
           {
               if ((((*itr1).position.y + 1 == (*itr).position.y) && (*itr1).position.x + 1 == (*itr).position.x))
               {
                   deleted_shootings.push_back((*itr).shooting);
                   swarm.erase(itr);
                   (shooting).erase(itr1);
                   ++count_killed;
               }
           }
           if ((*itr1).type == 1)  //right fire
           {
               if ((((*itr1).position.y + 1 == (*itr).position.y) && (*itr1).position.x - 1 == (*itr).position.x))
               {
                   deleted_shootings.push_back((*itr).shooting);
                   swarm.erase(itr);
                   (shooting).erase(itr1);
                   ++count_killed;
               }
           }
       }
   }
   return count_killed;
}

void Swarm::Fire(sf::Vector2u windsize)
{
    for (auto & enemy : swarm)
    {
        enemy.shooting.Add(enemy.position.x, enemy.position.y, true);
        enemy.shooting.Move(windsize, true);
    }
    for (auto & shooting : deleted_shootings)
        shooting.Move(windsize, true);
}

void Swarm::Render(sf::RenderWindow &window)
{
    sf::Sprite enemy_sprite(enemy_shape);
    sf::Vector2u s_size = enemy_shape.getSize();
    enemy_sprite.setOrigin(s_size.x / 2 - 8, s_size.y / 2);
    for (auto enemy : swarm)
    {
        enemy_sprite.setPosition(enemy.position.x * size, enemy.position.y * size);
        window.draw(enemy_sprite);
        enemy.shooting.Render(window);
    }
    for (auto & shooting : deleted_shootings)
        shooting.Render(window);
}

EnemyContainer &Swarm::Get_Swarm()
{
    return swarm;
}

std::vector<Shooting> &Swarm::Get_deleted_shootings()
{
    return deleted_shootings;
}

