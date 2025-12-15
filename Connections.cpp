#include "Connections.h"

Connections::Connections(Figure* figure_start, Figure* figure_end): line(sf::Lines, 2), figure1(figure_start), figure2(figure_end){
    this->line_color = sf::Color::Black;

    line[0].position = figure1->GetFigureCenter();
    line[1].position = figure2->GetFigureCenter();
    line[0].color = line_color;
    line[1].color = line_color;
}

void Connections::UpdateConnections(){
    line[0].position = figure1->GetFigureCenter();
    line[1].position = figure2->GetFigureCenter();
}

void Connections::DrawConnections(sf::RenderWindow& window){
    window.draw(line);
}

Figure* Connections::GetFigure1(){
    return figure1;
}

Figure* Connections::GetFigure2(){
    return figure2;
}
