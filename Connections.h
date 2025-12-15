#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"

class Connections{
private:
    sf::VertexArray line;
    Figure* figure1;
    Figure* figure2;
    sf::Vector2f pos1;
    sf::Vector2f pos2;
    sf::Color line_color;

public:
    Connections(Figure* figure1, Figure* figure2);
    void UpdateConnections();
    void DrawConnections(sf::RenderWindow& window);
    Figure* GetFigure1();
    Figure* GetFigure2();
    
};