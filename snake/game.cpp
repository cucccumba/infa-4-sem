#include "game.h"

Game::Game()
: window("Snake", sf::Vector2u(1920, 1080)), world(sf::Vector2u(1920, 1080))
{
    Snake Player(world.GetBlockSize(), 1, false);
    Snake bot1(world.GetBlockSize(), 2, true);
    Snake bot2(world.GetBlockSize(), 3, true);
    players.push_back(Player);
    players.push_back(bot1);
    players.push_back(bot2);
}

Game::~Game(){}

void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && players[0].GetDirection() != Direction::Down)
    {
        players[0].SetDirection(Direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && players[0].GetDirection() != Direction::Up)
    {
        players[0].SetDirection(Direction::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && players[0].GetDirection() != Direction::Right)
    {
        players[0].SetDirection(Direction::Left);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && players[0].GetDirection() != Direction::Left)
    {
        players[0].SetDirection(Direction::Right);
    }
}

void Game::Update()
{
    window.Update();
    float Elapsed = elapsed.asSeconds();
    float timestep = 1.0f / players[0].GetSpeed();
    if (Elapsed >= timestep)
    {
        for (auto & player : players)
            player.Tick(world.GetApple());
        for (auto & player : players)
            world.Update(player, players);
        elapsed -= sf::seconds(timestep);
        for (auto & player : players)
        {
            if (player.HasLost())
                player.Reset();
        }
    }
}

void Game::Render()
{
    window.ClearWindow();
    world.Render(*window.GetRenderWindow());
    for (auto itr = players.begin(); itr != players.end(); ++itr)
        (*itr).Render(*window.GetRenderWindow());
    window.Display();
}

void Game::Restartclock()
{
    elapsed += clock.restart();
}

Window *Game::GetWindow()
{
    return &window;
}

