#include "Figure.h"


Figure::Figure(sf::RenderWindow& window){
    figure_color = sf::Color(156, 154, 149);
    text_color = sf::Color::Black;
    border_color = sf::Color::Black;
    selected = false;
    
    str_size = 32;
    text = "New note...";
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    text_figure.setFont(font);
    text_figure.setCharacterSize(str_size);
    text_figure.setFillColor(text_color);
    text_figure.setString(text);
    
    // Вычисляем размер фигуры на основе текста
    sf::FloatRect textBounds = text_figure.getLocalBounds();
    sf::Vector2f figureSize(textBounds.width + 20, textBounds.height + 20);
    
    // Центрируем фигуру на экране
    position = sf::Vector2f((window.getSize().x - figureSize.x) / 2, (window.getSize().y - figureSize.y) / 2);
    UpdateFigure();
}

Figure::Figure(sf::RenderWindow& window, sf::Vector2f pos){
    figure_color = sf::Color(156, 154, 149);
    text_color = sf::Color::Black;
    border_color = sf::Color::Black;
    selected = false;
    
    str_size = 32;
    text = "New note...";
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    text_figure.setFont(font);
    text_figure.setCharacterSize(str_size);
    text_figure.setFillColor(text_color);
    text_figure.setString(text);
    
    // Используем переданную позицию
    position = pos;

    UpdateFigure();
}

void Figure::UpdateFigure(){
    text_figure.setCharacterSize(str_size);
    text_figure.setFillColor(text_color);
    text_figure.setString(text);
    text_figure.setFont(font);

    // Получаем размеры текста
    sf::FloatRect textBounds = text_figure.getLocalBounds();
    sf::Vector2f figureSize(textBounds.width + 20, textBounds.height + 20);
    
    // Настраиваем фигуру
    figure.setFillColor(figure_color);
    figure.setPosition(position);
    figure.setSize(figureSize);
    
    // Центрируем текст внутри фигуры
    text_figure.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text_figure.setPosition(position.x + figureSize.x / 2, position.y + figureSize.y / 2);

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

sf::Vector2f Figure::GetFigureCenter(){
    return  sf::Vector2f(figure.getPosition().x + figure.getSize().x/2, figure.getPosition().y + figure.getSize().y/2);
}

std::string Figure::GetFigureText(){
    return text;
}

sf::Color Figure::GetFigureColor(){
    return figure_color;
}

unsigned int Figure::GetFigureTextSize(){
    return str_size;
}

void Figure::SetSelected(bool sel){
    selected = sel;
}

void Figure::SetFigurePosition(sf::Vector2f pos){
    position = pos;
    UpdateFigure();
}

void Figure::SetFigureText(std::string txt){
    text = txt;
    UpdateFigure();
}

void Figure::SetFigureColor(sf::Color col){
    figure_color = col;
    UpdateFigure();
}

void Figure::SetFigureTextSize(unsigned int size){
    str_size = size;
    UpdateFigure();
}