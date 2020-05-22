#include "TextBox.h"

TextBox::TextBox()
{
    Setup(5,9,200,sf::Vector2f(0,0));
}
TextBox::TextBox(int visible, int charSize, int width, sf::Vector2f screen_pos)
{
    Setup(visible, charSize, width, screen_pos);
}
TextBox::~TextBox()
{
    Clear();
}

void TextBox::Setup(int visible, int charSize, int width, sf::Vector2f screen_pos)
{
    numVisible = visible;
    sf::Vector2f offset(2.0f, 2.0f);
    m_font.loadFromFile(R"(C:\Users\a-r-t\CLionProjects\game\arial.ttf)");
    m_content.setFont(m_font);
    m_content.setString("");
    m_content.setCharacterSize(charSize);
    m_content.setColor(sf::Color::White);
    m_content.setPosition(screen_pos + offset);
    m_backdrop.setSize(sf::Vector2f(width, (visible * (charSize * 1.2f))));
    m_backdrop.setFillColor(sf::Color(90,90,90,90));
    m_backdrop.setPosition(screen_pos);
}

void TextBox::Add(std::string message)
{
    m_messages.push_back(message);
    if(m_messages.size() < 6)
        return;
    m_messages.erase(m_messages.begin());
}

void TextBox::Clear()
{
    m_messages.clear();
}

void TextBox::Render(sf::RenderWindow &window)
{
    std::string content;
    for (auto & i : m_messages)
        content.append(i+"\n");
    if (content != "")
    {
        m_content.setString(content);
        window.draw(m_backdrop);
        window.draw(m_content);
    }
}