#include "Action.h"

Action::Action()
{

}

void Action::HandleEvent(sf::Event& event, sf::RenderWindow& window){
    if (event.type == sf::Event::MouseButtonPressed){
        AddFigure(window);
    }
}

void Action::AddFigure(sf::RenderWindow& window){
    figures.push_back(std::make_unique<Figure>(window));
}

void Action::DragFigure(Figure* figure){

}

void Action::DrawAllElements(sf::RenderWindow& window){
    for(auto& figure : figures){
        figure->DrawFigure(window);
    }
}

void Action::UpdateAllFigures(sf::RenderWindow& window){
    for(auto& figure : figures){
        figure->UpdateFigure();
    }
}