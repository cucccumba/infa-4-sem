#include "world.h"
#include <random>

World::World(sf::Vector2u windsize)
{
    blocksize = 16;
    windowsize = windsize;
    RespawnApple();
    appleshape.setFillColor(sf::Color::Red);
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

sf::Vector2i World::GetApple()
{
    return apple;
}

void World::RespawnApple()
{
    int maxX = (windowsize.x / blocksize) - 2;
    int maxY = (windowsize.y / blocksize) - 2;
    apple.x = rand() % maxX + 1;
    apple.y = rand() % maxY + 1;
    item = sf::Vector2i(apple.x, apple.y);
    appleshape.setPosition(item.x * blocksize, item.y * blocksize);
}

void World::Render(sf::RenderWindow &window)
{
    for (int i = 0; i < 4; ++i)
        window.draw(bounds[i]);
    window.draw(appleshape);
}

void World::Update(Snake &player, std::vector<Snake> players)
{
    if (player.GetPosition() == item)
    {
        player.Extend();
        player.IncreaseScore();
        RespawnApple();
    }

    int grindSizeX = windowsize.x / blocksize;
    int grindSizeY = windowsize.y / blocksize;

    //смотрим столкновение со стенками
    if (player.GetPosition().x <= 0 || player.GetPosition().y <= 0 || player.GetPosition().x >= grindSizeX - 1 || player.GetPosition().y >= grindSizeY - 1)
        player.Lose();

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
                    break;
                }
            }
        }
    }
}