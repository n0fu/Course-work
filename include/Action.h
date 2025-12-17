#pragma once
#include "Figure.h"
#include "Interface.h"
#include "Connections.h"
#include "EditMenu.h"
#include "FileManager.h"
#include <memory>

class Action{
private:
    std::vector<std::unique_ptr<Figure>> figures;
    std::vector<std::unique_ptr<Connections>> connections;
    Figure* selected_figure;
    Figure* delcon_figure1;
    Figure* delcon_figure2;
    std::unique_ptr<Button> file_button;
    std::unique_ptr<Button> settings_button;
    std::unique_ptr<Button> add_button;
    std::unique_ptr<Button> delete_button;
    std::unique_ptr<Button> connect_button;
    std::unique_ptr<Button> delete_connection_button;
    std::unique_ptr<EditMenu> edit_menu;
    sf::Vector2f drag_offset;
    sf::Color background_color = sf::Color::White;
    bool is_dark_theme = false;
    bool connection_mode = false;
    bool delete_connection_mode = false;

public:
    Action();
    void HandleEvent(sf::Event& event, sf::RenderWindow& window);
    void HandleMouseRightClick(sf::Vector2f mousePos, sf::RenderWindow& window);
    void HandleMouseLeftClick(sf::Vector2f mousePos, sf::RenderWindow& window);
    void HandleButtonClicked(sf::Vector2f mousePos, sf::RenderWindow& window);
    void HandleConnectionMode(sf::Vector2f mousePos, sf::RenderWindow& window);
    void HandleDeleteConnectionMode(sf::Vector2f mousePos, sf::RenderWindow& window);
    void AddConnection(Figure* figure1, Figure* figure2);
    void AddFigure(sf::RenderWindow& window);
    sf::Vector2f GetViewCenter() const { return worldView.getCenter(); }
    void DeleteFigure();
    void DrawFiguresAndConnections(sf::RenderWindow& window);
    void DrawUI(sf::RenderWindow& window);
    void UpdateAllFigures(sf::RenderWindow& window);
    void ButtonHover(sf::Vector2f mousePos);

    bool IsMouseOnFigure(Figure* figure, sf::Vector2f mousePos);
    void SaveMindMap();
    void LoadMindMap(sf::RenderWindow& window);
    void SetWorldView(const sf::View& view) { worldView = view; }
    sf::Vector2f MapPixelToWorld(sf::Vector2i pixelPos, sf::RenderWindow& window);

    void SetTheme();
    sf::Color GetBackgroundColor() const { return background_color; }
    
private:
    sf::View worldView;

    template<typename ButtonType> bool IsMouseOnButton(std::unique_ptr<ButtonType>& button, sf::Vector2f mousePos){
        sf::Vector2f pos = button->GetButtonPosition();
        sf::Vector2f size = button->GetButtonSize();
        return mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
           mousePos.y >= pos.y && mousePos.y <= pos.y + size.y;
    };
};