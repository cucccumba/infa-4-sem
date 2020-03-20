#include "game.h"

Game::Game()
: window("window", sf::Vector2u(1920, 1080))
{
    mashroomTexture.loadFromFile(R"(C:\Users\a-r-t\Pictures\mashroom.png)");
    mashroom.setTexture(mashroomTexture);
    increment = sf::Vector2i(400, 400);
}

Game::~Game(){}

void Game::Update()
{
    window.Update();
    MoveMushroom();
}

void Game::MoveMushroom()
{
    sf::Vector2u l_windSize = window.GetWindowSize();
    sf::Vector2u l_textSize = mashroomTexture.getSize();
    float Elapsed = elapsed.asSeconds();
    if((mashroom.getPosition().x > l_windSize.x - l_textSize.x && increment.x > 0) || (mashroom.getPosition().x < 0 && increment.x < 0))
    {
        increment.x = -increment.x;
    }
    if((mashroom.getPosition().y > l_windSize.y - l_textSize.y && increment.y > 0) || (mashroom.getPosition().y < 0 && increment.y < 0))
    {
        increment.y = -increment.y;
    }
    mashroom.setPosition(mashroom.getPosition().x + increment.x * Elapsed,mashroom.getPosition().y + increment.y * Elapsed);
}

void Game::Render()
{
    window.ClearWindow();
    window.Draw(mashroom);
    window.Display();
}

sf::Time Game::GetElapsed()
{
    return elapsed;
}

void Game::Restartclock()
{
    elapsed = clock.restart();
}

Window *Game::GetWindow()
{
    return &window;
}

