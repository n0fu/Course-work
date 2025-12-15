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
    Button();
    void DrawButton(sf::RenderWindow& window);
    void UpdateButton();
    sf::Vector2f GetButtonPosition();
    sf::Vector2f GetButtonSize();
};


class File: public Button{
public:
    File(std::string text, sf::Vector2f position);
};

class Settings: public Button{
public:
    Settings(std::string text, sf::Vector2f position);
};

class AddNote: public Button{
public:
    AddNote(std::string text, sf::Vector2f position);
};