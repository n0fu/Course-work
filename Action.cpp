#include "Action.h"

Action::Action()
{
    selected_figure = nullptr;
    file_button = new Button({0, 0}, "file");
    settings_button = new Button({file_button->GetButtonPosition().x + file_button->GetButtonSize().x, 0}, "settings");
    add_button = new Button({settings_button->GetButtonPosition().x + settings_button->GetButtonSize().x, 0}, "add note");
    delete_button = new Button({add_button->GetButtonPosition().x + add_button->GetButtonSize().x, 0}, "delete note");

}

void Action::HandleEvent(sf::Event& event, sf::RenderWindow& window){
    if (event.type == sf::Event::MouseButtonPressed){
        if (IsMouseOnButton(add_button, sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
            AddFigure(window);
        }

        for (auto& figure : figures){
            if (IsMouseOnFigure(figure.get(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                figure->SetSelected(true);
                selected_figure = figure.get();
                drag_offset.x = event.mouseButton.x - selected_figure->GetFigurePosition().x;
                drag_offset.y = event.mouseButton.y - selected_figure->GetFigurePosition().y;
            } else {
                figure->SetSelected(false);
                if (selected_figure == figure.get()){
                    selected_figure = nullptr;
                }
            }
        }
        
    }

    if (event.type == sf::Event::MouseMoved && selected_figure != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2f newPos;
        newPos.x = event.mouseMove.x - drag_offset.x;
        newPos.y = event.mouseMove.y - drag_offset.y;  
        selected_figure->SetFigurePosition(newPos);
    }
}

void Action::AddFigure(sf::RenderWindow& window){
    figures.push_back(std::make_unique<Figure>(window));
}


void Action::DrawAllElements(sf::RenderWindow& window){
    for(auto& figure : figures){
        figure->DrawFigure(window);
    }
    file_button->DrawButton(window);
    settings_button->DrawButton(window);
    add_button->DrawButton(window);
    delete_button->DrawButton(window);
}

void Action::UpdateAllFigures(sf::RenderWindow& window){
    for(auto& figure : figures){
        figure->UpdateFigure();
    }
    file_button->UpdateButton();
    settings_button->UpdateButton();
    add_button->UpdateButton();
    delete_button->UpdateButton();
}

bool Action::IsMouseOnFigure(Figure* figure, sf::Vector2f mousePos){
    return (mousePos.x >= figure->GetFigurePosition().x && mousePos.x <= figure->GetFigurePosition().x + figure->GetFigureSize().x &&
            mousePos.y >= figure->GetFigurePosition().y && mousePos.y <= figure->GetFigurePosition().y + figure->GetFigureSize().y);
}