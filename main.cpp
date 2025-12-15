#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Interface.h"
#include "Action.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 2.6.2 Project");
    File filebt("file", {0,0});
    Settings settingsbt("settings", {filebt.GetButtonPosition().x + filebt.GetButtonSize().x, 0});
    AddNote addnotebt("add note", {settingsbt.GetButtonPosition().x + settingsbt.GetButtonSize().x, 0});
    Action action;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            action.HandleEvent(event, window);

        }

        window.clear(sf::Color::White);
        action.UpdateAllFigures(window);
        action.DrawAllElements(window);
        filebt.DrawButton(window);
        settingsbt.DrawButton(window);
        addnotebt.DrawButton(window);
        window.display();
    }

    return 0;
}