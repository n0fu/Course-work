#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Interface.h"
#include "Action.h"

int main(){
    // Получаем размер рабочего стола
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    
    // Создаем окно на 80% от размера экрана для удобства
    unsigned int windowWidth = static_cast<unsigned int>(desktop.width * 0.8f);
    unsigned int windowHeight = static_cast<unsigned int>(desktop.height * 0.8f);
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "MindMap Editor", sf::Style::Default);
    
    // Центрируем окно на экране
    window.setPosition(sf::Vector2i((desktop.width - windowWidth) / 2, (desktop.height - windowHeight) / 2));
    
    Action action;
    
    // Переменные для панорамирования
    bool isPanning = false;
    sf::Vector2i lastMousePos;
    
    // Создаем две области просмотра
    sf::View uiView = window.getDefaultView();      // Фиксированная панель UI
    sf::View worldView = window.getDefaultView();   // Подвижная область с фигурами

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            
            // Обработка изменения размера окна
            if (event.type == sf::Event::Resized) {
                uiView.setSize(event.size.width, event.size.height);
                worldView.setSize(event.size.width, event.size.height);
            }
            
            // Панорамирование средней кнопкой мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
                isPanning = true;
                lastMousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            }
            
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle) {
                isPanning = false;
            }
            
            if (event.type == sf::Event::MouseMoved && isPanning) {
                sf::Vector2i currentMousePos(event.mouseMove.x, event.mouseMove.y);
                sf::Vector2i delta = lastMousePos - currentMousePos;
                
                worldView.move(static_cast<float>(delta.x), static_cast<float>(delta.y));
                
                lastMousePos = currentMousePos;
            }
            
            // Обновляем worldView в Action
            action.SetWorldView(worldView);
            action.HandleEvent(event, window);

        }

        window.clear(sf::Color::White);
        
        // Рисуем фигуры и соединения в подвижной области
        window.setView(worldView);
        action.UpdateAllFigures(window);
        action.DrawFiguresAndConnections(window);
        
        // Рисуем UI элементы в фиксированной области
        window.setView(uiView);
        action.DrawUI(window);
        
        window.display();
    }

    return 0;
}