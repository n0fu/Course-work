#include "Interface.h"

Button::Button(sf::Vector2f pos, std::string text){
    button_color = sf::Color::Blue;
    text_color = sf::Color::White;
    
    text_size = 20;
    text_string = text;
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    position = pos;
    // ========== НАЧАЛО ИСПРАВЛЕНИЯ: Правильная начальная настройка ==========
    text_button.setFont(font);
    text_button.setCharacterSize(text_size);
    text_button.setFillColor(text_color);
    text_button.setString(text_string);
    // ========== КОНЕЦ ИСПРАВЛЕНИЯ ==========

    UpdateButton();
}

void Button::UpdateButton(){
    // ========== НАЧАЛО ИСПРАВЛЕНИЯ: Аккуратное выравнивание текста кнопки ==========
    text_button.setCharacterSize(text_size);
    text_button.setFillColor(text_color);
    text_button.setString(text_string);
    text_button.setFont(font);

    // Получаем размеры текста
    sf::FloatRect textBounds = text_button.getLocalBounds();
    sf::Vector2f buttonSize(textBounds.width + 20, textBounds.height + 20);
    
    // Настраиваем кнопку
    button.setFillColor(button_color);
    button.setPosition(position);
    button.setSize(buttonSize);
    
    // Центрируем текст внутри кнопки
    text_button.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text_button.setPosition(position.x + buttonSize.x / 2, position.y + buttonSize.y / 2);
    // ========== КОНЕЦ ИСПРАВЛЕНИЯ ==========
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

void Button::SetButtonPosition(sf::Vector2f position){
    this->position = position;
    UpdateButton();
}

void Button::SetButtonText(std::string text){
    this->text_string = text;
    UpdateButton();
}

bool Button::IsMouseOnButton(sf::Vector2f mouse_pos){
    return button.getGlobalBounds().contains(mouse_pos);
}

void Button::SetButtonSize(sf::Vector2f size) {
    button.setSize(size);
    // Перецентрируем текст
    sf::FloatRect textBounds = text_button.getLocalBounds();
    text_button.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text_button.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void Button::SetButtonColor(sf::Color color) {
    button_color = color;
    button.setFillColor(button_color);
}

void Button::SetButtonTextColor(sf::Color color) {
    text_color = color;
    text_button.setFillColor(text_color);
}

sf::Color Button::GetButtonColor() const {
    return button_color;
}