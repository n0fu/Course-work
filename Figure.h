#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Figure {
private:
    sf::RectangleShape figure;
    sf::Text text_figure;
    sf::Font font;
    sf::Color figure_color;
    sf::Color text_color;
    sf::Color border_color;
    sf::Vector2f position;
    bool selected;
    unsigned int str_size;
    std::string text;


public:
    Figure(sf::RenderWindow& window);
    Figure(sf::RenderWindow& window, sf::Vector2f pos);
    void UpdateFigure();
    void DrawFigure(sf::RenderWindow& window);
    sf::Vector2f GetFigurePosition();
    sf::Vector2f GetFigureSize();
    sf::Vector2f GetFigureCenter();
    std::string GetFigureText();
    sf::Color GetFigureColor();
    unsigned int GetFigureTextSize();
    void SetSelected(bool sel);
    void SetFigureColor(sf::Color col);
    void SetFigureText(std::string text);
    void SetFigureTextSize(unsigned int size);
    void SetFigurePosition(sf::Vector2f pos);
};