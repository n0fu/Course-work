#include "Action.h"

Action::Action()
{
    selected_figure = nullptr;
    file_button = new Button({0, 0}, "file");
    settings_button = new Button({file_button->GetButtonPosition().x + file_button->GetButtonSize().x, 0}, "settings");
    add_button = new Button({settings_button->GetButtonPosition().x + settings_button->GetButtonSize().x, 0}, "add note");
    delete_button = new Button({add_button->GetButtonPosition().x + add_button->GetButtonSize().x, 0}, "delete note");
    connect_button = new Button({delete_button->GetButtonPosition().x + delete_button->GetButtonSize().x, 0}, "connect notes");
    delete_connection_button = new Button({connect_button->GetButtonPosition().x + connect_button->GetButtonSize().x, 0}, "delete connection mode");
}

void Action::HandleEvent(sf::Event& event, sf::RenderWindow& window){
    if (event.type == sf::Event::MouseButtonPressed){
        if (IsMouseOnButton(add_button, sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
            AddFigure(window);
        }

        if (IsMouseOnButton(delete_button, sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
            for (auto it = connections.begin(); it != connections.end();){
                if (it->get()->GetFigure1() == selected_figure || it->get()->GetFigure2() == selected_figure){
                    it = connections.erase(it);
                } else {
                    ++it;
                }
            }
            DeleteFigure();
        }

        if (IsMouseOnButton(connect_button, sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
            connection_mode = !connection_mode;
        }
        if (IsMouseOnButton(delete_connection_button, sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
            delete_connection_mode = !delete_connection_mode;
        }

        if (connection_mode){
            for (auto& figure : figures){
                if (IsMouseOnFigure(figure.get(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                    if (selected_figure != nullptr){
                        AddConnection(selected_figure, figure.get());
                        selected_figure = nullptr;
                    }
                }
            }
        }

        if (delete_connection_mode){
            if (delcon_figure1 == nullptr){
                for (auto& figure : figures){
                    if (IsMouseOnFigure(figure.get(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                        delcon_figure1 = figure.get();
                    }
                }
            } else {
                for (auto& figure : figures){
                    if (IsMouseOnFigure(figure.get(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
                        delcon_figure2 = figure.get();
                    }
                }

                for (auto it = connections.begin(); it != connections.end();){
                    if (((*it)->GetFigure1() == delcon_figure1 && (*it)->GetFigure2() == delcon_figure2) ||
                        ((*it)->GetFigure1() == delcon_figure2 && (*it)->GetFigure2() == delcon_figure1)){
                            it = connections.erase(it);
                            break;
                        } else {
                            ++it;
                        }
                }
                delcon_figure1 = nullptr;
                delcon_figure2 = nullptr;
            }
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

void Action::DeleteFigure(){
    for (auto it = figures.begin(); it != figures.end();){
        if (it->get() == selected_figure){
            selected_figure = nullptr;
            it = figures.erase(it);
        } else {
            ++it;
        }
    }
}

void Action::AddConnection(Figure* figure1, Figure* figure2){
    connections.push_back(std::make_unique<Connections>(figure1, figure2));
}

void Action::DrawAllElements(sf::RenderWindow& window){
    for(auto& connection : connections){
        connection->DrawConnections(window);
    }

    for(auto& figure : figures){
        figure->DrawFigure(window);
    }
    file_button->DrawButton(window);
    settings_button->DrawButton(window);
    add_button->DrawButton(window);
    delete_button->DrawButton(window);
    connect_button->DrawButton(window);
    delete_connection_button->DrawButton(window);
}

void Action::UpdateAllFigures(sf::RenderWindow& window){
    for(auto& connection : connections){
        connection->UpdateConnections();
    }

    for(auto& figure : figures){
        figure->UpdateFigure();
    }
    file_button->UpdateButton();
    settings_button->UpdateButton();
    add_button->UpdateButton();
    delete_button->UpdateButton();
    connect_button->UpdateButton();
    delete_connection_button->UpdateButton();
}

bool Action::IsMouseOnFigure(Figure* figure, sf::Vector2f mousePos){
    return (mousePos.x >= figure->GetFigurePosition().x && mousePos.x <= figure->GetFigurePosition().x + figure->GetFigureSize().x &&
            mousePos.y >= figure->GetFigurePosition().y && mousePos.y <= figure->GetFigurePosition().y + figure->GetFigureSize().y);
}