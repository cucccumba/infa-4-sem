#include "world.h"
#include <random>

World::World(sf::Vector2u windsize)
{
    blocksize = 16;
    windowsize = windsize;
    //RespawnApple();
    //appleshape.setFillColor(sf::Color::Red);
    appleshape.setRadius(blocksize / 2);

    // создаем рамку (стенки)
    for (int i = 0; i < 4; ++i)
        bounds[i].setFillColor(sf::Color::Blue);
    bounds[0].setSize(sf::Vector2f(windowsize.x, blocksize));
    bounds[0].setPosition(0, 0);
    bounds[1].setSize(sf::Vector2f(blocksize, windowsize.y));
    bounds[1].setPosition(0, 0);
    bounds[2].setSize(sf::Vector2f(windowsize.x, blocksize));
    bounds[3].setSize(sf::Vector2f(blocksize, windowsize.y));
    for (int i = 2; i < 4; ++i)
        bounds[i].setOrigin(bounds[i].getSize());
    bounds[2].setPosition(windowsize.x, windowsize.y);
    bounds[3].setPosition(windowsize.x, windowsize.y);
}

World::~World(){};

int World::GetBlockSize()
{
    return blocksize;
}

apple_container &World::GetApples()
{
    return appleContainer;
}

void World::RespawnApple(sf::Vector2u windsize)
{
    int chance = rand() < RAND_MAX / 20;

    if (chance)
    {
        int maxX = (windsize.x / blocksize) - 2;
        int maxY = (windsize.y / blocksize) - 2;
        int x = rand() % maxX + 1;
        int y = rand() % maxY + 1;
        appleContainer.Get_apples().push_back(apple(x, y, sf::Color::Red));
        //item = sf::Vector2i(apple.x, apple.y);
        //appleshape.setPosition(item.x * blocksize, item.y * blocksize);
    }
    else
        return;
}

void World::Render(sf::RenderWindow &window)
{
    sf::Vector2u windsize = window.getSize();
    bounds[0].setSize(sf::Vector2f(windsize.x, blocksize));
    bounds[0].setPosition(0, 0);
    bounds[1].setSize(sf::Vector2f(blocksize, windsize.y));
    bounds[1].setPosition(0, 0);
    bounds[2].setSize(sf::Vector2f(windsize.x, blocksize));
    bounds[3].setSize(sf::Vector2f(blocksize, windsize.y));
    for (int i = 2; i < 4; ++i)
        bounds[i].setOrigin(bounds[i].getSize());
    bounds[2].setPosition(windsize.x, windsize.y);
    bounds[3].setPosition(windsize.x, windsize.y);
    for (int i = 0; i < 4; ++i)
        window.draw(bounds[i]);
    for (auto i : appleContainer.Get_apples())
    {
        if (i.color == sf::Color::Red)
            appleshape.setFillColor(sf::Color::Red);
        else
            appleshape.setFillColor(sf::Color::Yellow);
        appleshape.setPosition(i.pos.x * blocksize, i.pos.y * blocksize);
        window.draw(appleshape);
    }

}

void World::Update(Snake &player, std::vector<Snake> players, TextBox &textBox, sf::Vector2u windsize)
{
    for (auto it = appleContainer.Get_apples().begin(); it < appleContainer.Get_apples().end(); ++it)
    {
        ++(*it).i;
        if ((*it).i > 50)
            (*it).color = sf::Color::Yellow;
        if ((*it).i > 100)
            appleContainer.Get_apples().erase(it);
        if (player.GetPosition() == (*it).pos)
        {
            player.Extend();
            player.IncreaseScore();
            textBox.Add("Player " + std::to_string(player.GetNumber()) +" ate an apple. Score: " + std::to_string(player.GetScore()));
            appleContainer.Get_apples().erase(it);
            //RespawnApple();
        }

    }

    int grindSizeX = windsize.x / blocksize;
    int grindSizeY = windsize.y / blocksize;

    //смотрим столкновение со стенками
    if (player.GetPosition().x <= 0 || player.GetPosition().y <= 0 || player.GetPosition().x >= grindSizeX - 1 || player.GetPosition().y >= grindSizeY - 1)
    {
        player.Lose();
        textBox.Add("Player " + std::to_string(player.GetNumber()) + " hit the wall");
    }


    //смотрим столкновение с другими змеями
    sf::Vector2i head = player.GetPosition();
    int PlayerNum = player.GetNumber();
    for (auto & itr : players)
    {
        if (itr.GetNumber() != PlayerNum)
        {
            for (auto & itr1 : itr.GetSnakebody())
            {
                if (itr1.position == head)
                {
                    player.Lose();
                    textBox.Add("Player " + std::to_string(player.GetNumber()) + " hit Player " + std::to_string(itr.GetNumber()));
                    break;
                }
            }
        }
    }
}