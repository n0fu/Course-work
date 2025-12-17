#include "Action.h"

Action::Action()
{
    selected_figure = nullptr;
    
    file_button = new Button({0, 0}, "file");
    file_button->SetButtonColor(sf::Color::White);
    file_button->SetButtonTextColor(sf::Color::Black);
    
    settings_button = new Button({file_button->GetButtonSize().x, 0}, "theme");
    settings_button->SetButtonColor(sf::Color::White);
    settings_button->SetButtonTextColor(sf::Color::Black);
    
    add_button = new Button({settings_button->GetButtonSize().x + settings_button->GetButtonPosition().x, 0}, "add note");
    add_button->SetButtonColor(sf::Color::White);
    add_button->SetButtonTextColor(sf::Color::Black);
    
    delete_button = new Button({add_button->GetButtonSize().x + add_button->GetButtonPosition().x, 0}, "delete note");
    delete_button->SetButtonColor(sf::Color::White);
    delete_button->SetButtonTextColor(sf::Color::Black);
    
    connect_button = new Button({delete_button->GetButtonSize().x + delete_button->GetButtonPosition().x, 0}, "connect notes");
    connect_button->SetButtonColor(sf::Color::White);
    connect_button->SetButtonTextColor(sf::Color::Black);

    delete_connection_button = new Button({connect_button->GetButtonSize().x + connect_button->GetButtonPosition().x, 0}, "delete connection");
    delete_connection_button->SetButtonColor(sf::Color::White);
    delete_connection_button->SetButtonTextColor(sf::Color::Black);
    
    edit_menu = new EditMenu();
}

void Action::HandleEvent(sf::Event& event, sf::RenderWindow& window){
    if (event.type == sf::Event::TextEntered && edit_menu->IsTextEditing()) {
        edit_menu->HandleTextInput(static_cast<char>(event.text.unicode));
    }

    if (event.type == sf::Event::KeyPressed && edit_menu->IsTextEditing()) {
        edit_menu->HandleKeyPress(event.key.code);
    }

    if (event.type == sf::Event::MouseMoved){
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        ButtonHover(mousePos);
    }


    if (event.type == sf::Event::MouseButtonPressed){
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f worldMousePos = MapPixelToWorld(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), window);
        
        if (event.mouseButton.button == sf::Mouse::Right) {
            for (auto& figure : figures) {
                if (IsMouseOnFigure(figure.get(), worldMousePos)) {
                    selected_figure = figure.get();
                    figure->SetSelected(true);
                    // Инициализируем меню текущими значениями фигуры
                    edit_menu->SetCurrentText(figure->GetFigureText());
                    edit_menu->SetSelectedColor(figure->GetFigureColor());
                    edit_menu->SetSelectedTextSize(figure->GetFigureTextSize());
                    edit_menu->ShowMenu(figure->GetFigurePosition(), figure->GetFigureSize(), window.getSize());
                    return;
                }
            }
            edit_menu->HideMenu();
            return;
        }
        
        // Левый клик - обработка меню
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (edit_menu->IsVisible()) {
                int menuChoice = edit_menu->HandleClick(mousePos);
                
                if (menuChoice >= 100 && menuChoice <= 105) { // Выбор цвета
                    if (selected_figure) {
                        selected_figure->SetFigureColor(edit_menu->GetSelectedColor());
                        selected_figure->UpdateFigure();
                    }
                } else if (menuChoice >= 200 && menuChoice <= 202) { // Выбор размера текста
                    if (selected_figure) {
                        selected_figure->SetFigureTextSize(edit_menu->GetSelectedTextSize());
                        selected_figure->UpdateFigure();
                    }
                } else if (menuChoice == 1) { // Apply
                    if (selected_figure) {
                        if (!edit_menu->GetCurrentText().empty()) {
                            selected_figure->SetFigureText(edit_menu->GetCurrentText());
                        }
                        selected_figure->SetFigureColor(edit_menu->GetSelectedColor());
                        selected_figure->SetFigureTextSize(edit_menu->GetSelectedTextSize());
                        selected_figure->UpdateFigure();
                    }
                    edit_menu->HideMenu();
                } else if (menuChoice == -2) { // Клик по полю ввода
                    return;
                }
                
                if (!edit_menu->IsMouseInMenu(mousePos)) {
                    edit_menu->HideMenu();
                }
                return;
            }
            
            if (!edit_menu->IsMouseInMenu(mousePos)) {
                edit_menu->HideMenu();
            }
        }
        
        if (IsMouseOnButton(file_button, mousePos)){
            // Простое меню - Ctrl для сохранения, иначе загрузка
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                SaveMindMap();
            } else {
                LoadMindMap(window);
            }
        }
        
        if (IsMouseOnButton(add_button,mousePos)){
            AddFigure(window);
        }

        if (IsMouseOnButton(delete_button, mousePos)){
            for (auto it = connections.begin(); it != connections.end();){
                if (it->get()->GetFigure1() == selected_figure || it->get()->GetFigure2() == selected_figure){
                    it = connections.erase(it);
                } else {
                    ++it;
                }
            }
            DeleteFigure();
        }

        if (IsMouseOnButton(connect_button, mousePos)){
            connection_mode = !connection_mode;
        }
        if (IsMouseOnButton(delete_connection_button, mousePos)){
            delete_connection_mode = !delete_connection_mode;
        }

        if (connection_mode){
            connect_button->SetButtonColor(sf::Color(169, 173, 196));
            for (auto& figure : figures){
                if (IsMouseOnFigure(figure.get(), worldMousePos)){
                    if (selected_figure != nullptr){
                        AddConnection(selected_figure, figure.get());
                        selected_figure = nullptr;
                    }
                }
            }
        } else {
            connect_button->SetButtonColor(sf::Color::White);
        }

        if (delete_connection_mode){
            delete_connection_button->SetButtonColor(sf::Color(169, 173, 196));
            if (delcon_figure1 == nullptr){
                for (auto& figure : figures){
                    if (IsMouseOnFigure(figure.get(), worldMousePos)){
                        delcon_figure1 = figure.get();
                    }
                }
            } else if (delcon_figure2 == nullptr){
                for (auto& figure : figures){
                    if (IsMouseOnFigure(figure.get(), worldMousePos)){
                        delcon_figure2 = figure.get();
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
            }
        } else {
            delete_connection_button->SetButtonColor(sf::Color::White);
        }

        for (auto& figure : figures){
            if (IsMouseOnFigure(figure.get(), worldMousePos)){
                figure->SetSelected(true);
                selected_figure = figure.get();
                drag_offset.x = worldMousePos.x - selected_figure->GetFigurePosition().x;
                drag_offset.y = worldMousePos.y - selected_figure->GetFigurePosition().y;
            } else {
                figure->SetSelected(false);
                if (selected_figure == figure.get()){
                    selected_figure = nullptr;
                }
            }
        }
    }

    if (event.type == sf::Event::MouseMoved && selected_figure != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2f worldMousePos = MapPixelToWorld(sf::Vector2i(event.mouseMove.x, event.mouseMove.y), window);
        sf::Vector2f newPos;
        newPos.x = worldMousePos.x - drag_offset.x;
        newPos.y = worldMousePos.y - drag_offset.y;  
        selected_figure->SetFigurePosition(newPos);
    }
}

void Action::AddFigure(sf::RenderWindow& window){
    // Создаем фигуру в центре текущего вида
    sf::Vector2f viewCenter = worldView.getCenter();
    figures.push_back(std::make_unique<Figure>(window, viewCenter));
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
    edit_menu->DrawMenu(window);
}

void Action::DrawFiguresAndConnections(sf::RenderWindow& window){
    for(auto& connection : connections){
        connection->DrawConnections(window);
    }

    for(auto& figure : figures){
        figure->DrawFigure(window);
    }
}

void Action::DrawUI(sf::RenderWindow& window){
    file_button->DrawButton(window);
    settings_button->DrawButton(window);
    add_button->DrawButton(window);
    delete_button->DrawButton(window);
    connect_button->DrawButton(window);
    delete_connection_button->DrawButton(window);
    edit_menu->DrawMenu(window);
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

void Action::StartTextEditing() {
    if (selected_figure) {
        // Простая реализация - изменить текст на фиксированный
        selected_figure->SetFigureText("Edited!");
        selected_figure->UpdateFigure();
    }
}

void Action::ShowColorPicker() {
    if (selected_figure) {
        // Простая реализация - циклически менять цвет
        static int colorIndex = 0;
        sf::Color colors[] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};
        selected_figure->SetFigureColor(colors[colorIndex % 4]);
        selected_figure->UpdateFigure();
        colorIndex++;
    }
}

void Action::SaveMindMap() {
    std::string filename = FileManager::SaveFileDialog();
    if (!filename.empty()) {
        FileManager::SaveMindMap(filename, figures, connections);
    }
}

void Action::LoadMindMap(sf::RenderWindow& window) {
    std::string filename = FileManager::OpenFileDialog();
    if (!filename.empty()) {
        FileManager::LoadMindMap(filename, figures, connections, window);
        selected_figure = nullptr;
    }
}

sf::Vector2f Action::MapPixelToWorld(sf::Vector2i pixelPos, sf::RenderWindow& window) {
    return window.mapPixelToCoords(pixelPos, worldView);
}

void Action::ButtonHover(sf::Vector2f mousePos){
    if (IsMouseOnButton(file_button, mousePos)){
        file_button->SetButtonColor(sf::Color(169,173,196));
    } else {
        file_button->SetButtonColor(sf::Color::White);
    }

    if (IsMouseOnButton(settings_button, mousePos)){
        settings_button->SetButtonColor(sf::Color(169, 173, 196));
    } else {
        settings_button->SetButtonColor(sf::Color::White);
    }

    if (IsMouseOnButton(add_button, mousePos)){
        add_button->SetButtonColor(sf::Color(169, 173, 196));
    } else {
        add_button->SetButtonColor(sf::Color::White);
    }

    if (IsMouseOnButton(delete_button, mousePos)){
        delete_button->SetButtonColor(sf::Color(169, 173, 196));
    } else {
        delete_button->SetButtonColor(sf::Color::White);
    }

    if (!connection_mode){
        if (IsMouseOnButton(connect_button, mousePos)){
        connect_button->SetButtonColor(sf::Color(169, 173, 196));
        } else {
            connect_button->SetButtonColor(sf::Color::White);
        }
    }


    if (!delete_connection_mode){
        if (IsMouseOnButton(delete_connection_button, mousePos)){
            delete_connection_button->SetButtonColor(sf::Color(169, 173, 196));
        } else {
            delete_connection_button->SetButtonColor(sf::Color::White);
        }
    }
}