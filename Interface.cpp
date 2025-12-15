#include "Interface.h"

Button::Button(){
    button_color = sf::Color::Blue;
    text_color = sf::Color::White;
    
    text_size = 20;
    text_string = "Button";
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    position = sf::Vector2f(0, 0);
    text_button.setCharacterSize(text_size);
    text_button.setFillColor(text_color);
    text_button.setString(text_string);
    text_button.setPosition(position.x, position.y);
    text_button.setFont(font);

    button.setFillColor(button_color);
    button.setPosition(position.x - 5, position.y + 5);
    button.setSize(sf::Vector2f(text_button.getGlobalBounds().width + 10, text_button.getGlobalBounds().height + 10));

    UpdateButton();
}

void Button::UpdateButton(){
    text_button.setCharacterSize(text_size);
    text_button.setFillColor(text_color);
    text_button.setString(text_string);
    text_button.setPosition(position.x, position.y);
    text_button.setFont(font);

    button.setFillColor(button_color);
    button.setPosition(position.x - 5, position.y + 5);
    button.setSize(sf::Vector2f(text_button.getGlobalBounds().width + 10, text_button.getGlobalBounds().height + 10));
}

void Button::DrawButton(sf::RenderWindow &window){
    window.draw(button);
    window.draw(text_button);
}

sf::Vector2f Button::GetButtonPosition(){
    return this->position;
}

sf::Vector2f Button::GetButtonSize(){
    return sf::Vector2f(button.getGlobalBounds().width, button.getGlobalBounds().height);
}

File::File(std::string text, sf::Vector2f position): Button(){
    text_string = text;
    this->position = position;
    UpdateButton();
}

Settings::Settings(std::string text, sf::Vector2f position): Button(){
    text_string = text;
    this->position = position;
    UpdateButton();
}

AddNote::AddNote(std::string text, sf::Vector2f position): Button(){
    text_string = text;
    this->position = position;
    UpdateButton();
}