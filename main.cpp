#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Interface.h"
#include "Action.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 2.6.2 Project");
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
        window.display();
    }

    return 0;
}