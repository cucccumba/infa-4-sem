#pragma once

#include <string>
#include <SFML/Graphics.hpp>
class Window
{
public:
    Window();  //! default window with 640x480 size
    Window(const std::string &title, const sf::Vector2u size);
    ~Window();

    void ClearWindow();
    void Display();
    void Update();  //! check new events
    bool IsDone();  //! point if close button is pressed
    bool IsFullScreen();
    sf::Vector2u GetWindowSize();
    void ToggleFullscreen();
    void Draw(sf::Drawable& drawable);
    sf::RenderWindow* GetRenderWindow();

private:
    void Setup(const std::string& title, const sf::Vector2u& size);
    void Destroy();
    void Create();
    sf::RenderWindow window;
    sf::Vector2u windowSize;
    std::string windowTitle;
    bool isDone;
    bool isFullscreen;
};