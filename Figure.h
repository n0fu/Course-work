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
    void UpdateFigure();
    void DrawFigure(sf::RenderWindow& window);
    


};