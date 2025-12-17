#pragma once
#include <SFML/Graphics.hpp>

class Button{
protected:
    sf::RectangleShape button;
    sf::Text text_button;
    sf::Font font;
    sf::Color button_color;
    sf::Color text_color;
    sf::Vector2f position;
    std::string text_string;
    unsigned int text_size;

public:
    Button(sf::Vector2f pos, std::string text);
    void DrawButton(sf::RenderWindow& window);
    void UpdateButton();
    void SetButtonPosition(sf::Vector2f pos);
    void SetButtonText(std::string text);
    void SetButtonSize(sf::Vector2f size);
    void SetButtonColor(sf::Color color);
    void SetButtonTextColor(sf::Color color);
    bool IsMouseOnButton(sf::Vector2f mousePos);
    sf::Color GetButtonColor() const;
    sf::Vector2f GetButtonPosition();
    sf::Vector2f GetButtonSize();
};
