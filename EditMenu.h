#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Interface.h"

class EditMenu{
private:
    sf::RectangleShape background;
    
    // Поле ввода текста
    sf::RectangleShape textInputBox;
    sf::Text inputText;
    std::string currentText;
    bool isTextEditing;
    
    // Цветовые круги
    std::vector<sf::CircleShape> colorCircles;
    std::vector<sf::Color> colors;
    sf::Color selectedColor;
    
    // Кнопки размера текста
    Button* smallTextButton;
    Button* mediumTextButton;
    Button* largeTextButton;
    Button* applyButton;
    
    bool isVisible;
    sf::Vector2f menu_position;
    sf::Font font;
    unsigned int selectedTextSize;

public:
    EditMenu();
    ~EditMenu();
    void ShowMenu(sf::Vector2f figurePos, sf::Vector2f figureSize, sf::Vector2u windowSize);
    void HideMenu();
    void DrawMenu(sf::RenderWindow& window);
    int HandleClick(sf::Vector2f mousePos);
    void HandleTextInput(char c);
    void HandleKeyPress(sf::Keyboard::Key key);
    
    bool IsVisible() const { return isVisible; }
    bool IsMouseInMenu(sf::Vector2f mousePos);
    bool IsTextEditing() const { return isTextEditing; }
    std::string GetCurrentText() const { return currentText; }
    sf::Color GetSelectedColor() const { return selectedColor; }
    unsigned int GetSelectedTextSize() const { return selectedTextSize; }
    void SetCurrentText(const std::string& text);
    void SetSelectedColor(sf::Color color);
    void SetSelectedTextSize(unsigned int size);

};

