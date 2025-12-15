#pragma once
#include "Figure.h"
#include "Interface.h"
#include <memory>

class Action{
private:
    std::vector<std::unique_ptr<Figure>> figures;
    Figure* selected_figure;
    File* file_button;
    Settings* settings_button;
    AddNote* add_note_button;

public:
    Action();
    void HandleEvent(sf::Event& event, sf::RenderWindow& window);
    void AddFigure(sf::RenderWindow& window);
    void DragFigure(Figure* figure);
    void DrawAllElements(sf::RenderWindow& window);
    void UpdateAllFigures(sf::RenderWindow& window);
};