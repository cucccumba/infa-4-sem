#include "game.h"

Game::Game()
: window("Snake", sf::Vector2u(1920, 1080)),  ship(16, sf::Vector2u(1920, 1080)), world(16)
{
    textBox.Setup(5, 14, 350, sf::Vector2f(10, 10));
    textBox.Add("Starship game");
    space_texture.loadFromFile(R"(C:\Users\a-r-t\Pictures\space.jpg)");
}

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
    float Elapsed_Enemies_spawn = elapsed_Enemies_spawn.asSeconds();
    float Elapsed_Enemies_move = elapsed_Enemies_move.asSeconds();
    float timestep = 1.0f / ship.GetSpeed();
    if (Elapsed >= timestep)
    {
        if (Elapsed_Enemies_spawn >= 5)
        {
            world.Spawn_Enemies(window.GetWindowSize(), world.GetBlockSize());
            elapsed_Enemies_spawn -= sf::seconds(Elapsed_Enemies_spawn);
        }
        ship.Tick();
        int killed = KillEnemy();
        if (killed > 0)
        {
            ship.IncreaseScore(killed);
            textBox.Add("Score: " + std::to_string(ship.GetScore()));
        }
        if (Elapsed_Enemies_move >= 0.5)
        {
            world.Tick(window.GetWindowSize());
            elapsed_Enemies_move -= sf::seconds(Elapsed_Enemies_move);
        }
        world.Check_hits_to_ship(ship);
        if (ship.HasLost())
        {
            textBox.Add("Game over");
        }
        elapsed -= sf::seconds(timestep);
    }
}
void Game::Render()
{
    window.ClearWindow();
    sf::Sprite space_sprite(space_texture);
    space_sprite.setPosition(0, 0);
    window.GetRenderWindow()->draw(space_sprite);
    ship.Render(*window.GetRenderWindow());
    world.Render(*window.GetRenderWindow());
    textBox.Render(*window.GetRenderWindow());
    window.Display();
}

void Game::Restartclock()
{
    sf::Time time = clock.restart();
    elapsed += time;
    elapsed_Enemies_spawn += time;
    elapsed_Enemies_move += time;
}

Window *Game::GetWindow()
{
    return &window;
}

int Game::KillEnemy()
{
    return world.Kill_Enemy(ship.GetShooting());
}
