#include "game.h"

Game::Game()
: window("Snake", sf::Vector2u(1920, 1080)), snake(world.GetBlockSize()), world(sf::Vector2u(1920, 1080))
{}

Game::~Game(){}

void Game::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.GetDirection() != Direction::Down)
    {
        snake.SetDirection(Direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.GetDirection() != Direction::Up)
    {
        snake.SetDirection(Direction::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.GetDirection() != Direction::Right)
    {
        snake.SetDirection(Direction::Left);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.GetDirection() != Direction::Left)
    {
        snake.SetDirection(Direction::Right);
    }
}

void Game::Update()
{
    window.Update();
    float Elapsed = elapsed.asSeconds();
    float timestep = 1.0f / snake.GetSpeed();
    if (Elapsed >= timestep)
    {
        snake.Tick();
        world.Update(snake);
        elapsed -= sf::seconds(timestep);
        if (snake.HasLost())
            snake.Reset();
    }
}

void Game::Render()
{
    window.ClearWindow();
    world.Render(*window.GetRenderWindow());
    snake.Render(*window.GetRenderWindow());
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

