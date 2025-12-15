#include "Figure.h"


Figure::Figure(sf::RenderWindow& window){
    figure_color = sf::Color::Blue;
    text_color = sf::Color::White;
    border_color = sf::Color::Red;
    selected = false;
    
    str_size = 32;
    text = "New note...";
    if (!font.loadFromFile("arial.ttf")) {
        // Пробуем системный путь
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    position = sf::Vector2f(window.getSize().x/2, window.getSize().y/2);
    text_figure.setCharacterSize(str_size);
    text_figure.setFillColor(text_color);
    text_figure.setString(text);
    text_figure.setPosition(position.x, position.y);
    text_figure.setFont(font);

    figure.setFillColor(figure_color);
    figure.setPosition(position.x - 5, position.y + 5);
    figure.setSize(sf::Vector2f(text_figure.getGlobalBounds().width + 10, text_figure.getGlobalBounds().height + 10));

    UpdateFigure();
}

void Figure::UpdateFigure(){
    text_figure.setCharacterSize(str_size);
    text_figure.setFillColor(text_color);
    text_figure.setString(text);
    text_figure.setPosition(position.x, position.y);
    text_figure.setFont(font);

    figure.setFillColor(figure_color);
    figure.setPosition(position.x, position.y);
    figure.setSize(sf::Vector2f(text_figure.getGlobalBounds().width + 10, text_figure.getGlobalBounds().height + 10));

    if (selected){
        figure.setOutlineThickness(2);
        figure.setOutlineColor(border_color);
    } else {
        figure.setOutlineThickness(0);
    }
}

void Figure::DrawFigure(sf::RenderWindow& window){
    window.draw(figure);
    window.draw(text_figure);
}

sf::Vector2f Figure::GetFigurePosition(){
    return  sf::Vector2f(figure.getPosition().x, figure.getPosition().y);
}

sf::Vector2f Figure::GetFigureSize(){
    return  sf::Vector2f(figure.getSize().x, figure.getSize().y);
}

void Figure::SetSelected(bool sel){
    selected = sel;
}

void Figure::SetFigurePosition(sf::Vector2f pos){
    position = pos;
    UpdateFigure();
}