#pragma once
#include <SFML/Graphics.hpp>

class TextBox
{
public:
    TextBox();
    TextBox(int visible, int charsize, int width, sf::Vector2f screen_pos);
    ~TextBox();

    void Setup(int visible, int charSize, int width, sf::Vector2f screen_pos);
    void Add(std::string message);
    void Clear();
    void Render(sf::RenderWindow& window);

private:
    std::vector<std::string> m_messages;
    int numVisible;
    sf::RectangleShape m_backdrop;
    sf::Font m_font;
    sf::Text m_content;
};