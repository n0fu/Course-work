#pragma once
#include "Figure.h"
#include "Interface.h"
#include "Connections.h"
#include <memory>

class Action{
private:
    std::vector<std::unique_ptr<Figure>> figures;
    std::vector<std::unique_ptr<Connections>> connections;
    Figure* selected_figure;
    Figure* delcon_figure1;
    Figure* delcon_figure2;
    Button* file_button;
    Button* settings_button;
    Button* add_button;
    Button* delete_button;
    Button* connect_button;
    Button* delete_connection_button;
    sf::Vector2f drag_offset;
    bool connection_mode = false;
    bool delete_connection_mode = false;

public:
    Action();
    void HandleEvent(sf::Event& event, sf::RenderWindow& window);
    void AddConnection(Figure* figure1, Figure* figure2);
    void AddFigure(sf::RenderWindow& window);
    void DeleteFigure();
    void DragFigure(Figure* figure, double offset_x, double offset_y);
    void DrawAllElements(sf::RenderWindow& window);
    void UpdateAllFigures(sf::RenderWindow& window);

    bool IsMouseOnFigure(Figure* figure, sf::Vector2f mousePos);

    template<typename ButtonType> bool IsMouseOnButton(ButtonType* button, sf::Vector2f mousePos){
        sf::Vector2f pos = button->GetButtonPosition();
        sf::Vector2f size = button->GetButtonSize();
        return mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
           mousePos.y >= pos.y && mousePos.y <= pos.y + size.y;
    };
};