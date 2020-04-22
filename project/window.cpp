#include "window.h"

Window::Window()
{
    Setup("Window", sf::Vector2u(640, 480));
}
Window::Window(const std::string &title, const sf::Vector2u size)
{
    Setup(title, size);
}
Window::~Window()
{
    Destroy();
}

void Window::Setup(const std::string& title, const sf::Vector2u& size)
{
    windowSize = size;
    windowTitle = title;
    isDone = false;
    isFullscreen = false;
    Create();
}
void Window::Create()
{
    auto style = (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    window.create({windowSize.x, windowSize.y, 32}, windowTitle, style);
}
void Window::Destroy()
{
    window.close();
}

void Window::Update()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            isDone = true;
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            ToggleFullscreen();
    }
}
void Window::ToggleFullscreen()
{
    isFullscreen = !isFullscreen;
    Destroy();
    Create();
}

void Window::ClearWindow()
{
    window.clear(sf::Color::Black);
}
void Window::Display()
{
    window.display();
}

bool Window::IsDone()
{
    return isDone;
}
bool Window::IsFullScreen()
{
    return isFullscreen;
}
sf::Vector2u Window::GetWindowSize()
{
    return windowSize;
}
void Window::Draw(sf::Drawable &drawable)
{
    window.draw(drawable);
}

sf::RenderWindow* Window::GetRenderWindow()
{
    return &window;
}
