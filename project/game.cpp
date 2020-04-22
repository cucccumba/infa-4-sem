#include "game.h"

Game::Game()
: window("Snake", sf::Vector2u(1920, 1080)),  ship(16, sf::Vector2u(1920, 1080)), swarm(16)
{}

Game::~Game(){}

void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ship.GetPosition().y > 0)
    {
        ship.SetDirection(Direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ship.GetPosition().y < (window.GetWindowSize().y / ship.GetSize()))
    {
        ship.SetDirection(Direction::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ship.GetPosition().x > 0)
    {
        ship.SetDirection(Direction::Left);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ship.GetPosition().x < (window.GetWindowSize().x / ship.GetSize()))
    {
        ship.SetDirection(Direction::Right);
    }
    else
    {
        ship.SetDirection(Direction::None);
    }
}

void Game::Update()
{
    window.Update();
    float Elapsed = elapsed.asSeconds();
    float ElapsedEnemies = elapsedEnemies.asSeconds();
    float timestep = 1.0f / ship.GetSpeed();
    if (Elapsed >= timestep)
    {
        int x = 5;
        int y = 1;
        if (ElapsedEnemies > 3)
        {
            for (int i = 0; i < 3; ++i)
            {
                swarm.Add(x, y);
                x += 10;
            }
            elapsedEnemies -= sf::seconds(ElapsedEnemies);
        }
        ship.Tick();
        KillEnemy();
        swarm.Move(window.GetWindowSize());
        elapsed -= sf::seconds(timestep);
    }
}
void Game::Render()
{
    window.ClearWindow();
    ship.Render(*window.GetRenderWindow());
    swarm.Render(*window.GetRenderWindow());
    window.Display();
}

void Game::Restartclock()
{
    elapsed += clock.restart();
    elapsedEnemies += elapsed;
}

Window *Game::GetWindow()
{
    return &window;
}

void Game::KillEnemy()
{
    swarm.Kill((*ship.GetShooting()).GetShootingC());
    swarm.Kill((*ship.GetShooting()).GetShootingL());
    swarm.Kill((*ship.GetShooting()).GetShootingR());
}
