#include "EditMenu.h"

EditMenu::EditMenu() : isVisible(false), isTextEditing(false), selectedColor(sf::Color::Blue), selectedTextSize(24) {
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    
    // Настройка фона меню
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);
    
    // Настройка поля ввода текста
    textInputBox.setFillColor(sf::Color::White);
    textInputBox.setOutlineThickness(1);
    textInputBox.setOutlineColor(sf::Color::Black);
    
    inputText.setFont(font);
    inputText.setCharacterSize(16);
    inputText.setFillColor(sf::Color::Black);
    
    // Создание цветов для кругов
    colors = {sf::Color(115, 138, 132), sf::Color(200, 154, 131), sf::Color(192, 108, 131), 
              sf::Color(144, 180, 143), sf::Color(159, 208, 214), sf::Color(236, 213, 119)};
    
    // Создание цветовых кругов
    for (size_t i = 0; i < colors.size(); ++i) {
        sf::CircleShape circle(15);
        circle.setFillColor(colors[i]);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        colorCircles.push_back(circle);
    }
    
    // Создание кнопок размера текста
    smallTextButton = new Button({0, 0}, "S");
    mediumTextButton = new Button({0, 0}, "M");
    largeTextButton = new Button({0, 0}, "L");
    applyButton = new Button({0, 0}, "Apply");
}

EditMenu::~EditMenu() {
    delete smallTextButton;
    delete mediumTextButton;
    delete largeTextButton;
    delete applyButton;
}

void EditMenu::ShowMenu(sf::Vector2f figurePos, sf::Vector2f figureSize, sf::Vector2u windowSize) {
    // Позиционируем меню в центре экрана
    float menuWidth = 200;
    float menuHeight = 300;
    menu_position = {(windowSize.x - menuWidth) / 2, (windowSize.y - menuHeight) / 2};
    isVisible = true;
    
    // Настройка фона
    background.setPosition(menu_position);
    background.setSize({menuWidth, menuHeight});
    
    // Настройка поля ввода текста
    float textBoxWidth = menuWidth - 20;
    textInputBox.setPosition({menu_position.x + 10, menu_position.y + 30});
    textInputBox.setSize({textBoxWidth, 30});
    inputText.setPosition({menu_position.x + 15, menu_position.y + 35});
    
    // Позиционирование цветовых кругов (2 ряда по 3)
    float circleStartX = menu_position.x + (menuWidth - 150) / 2;
    for (size_t i = 0; i < colorCircles.size(); ++i) {
        float x = circleStartX + (i % 3) * 50;
        float y = menu_position.y + 90 + (i / 3) * 50;
        colorCircles[i].setPosition(x, y);
    }
    
    // Позиционирование кнопок размера текста
    float buttonWidth = 50;
    float buttonSpacing = (menuWidth - 3 * buttonWidth) / 4;
    
    smallTextButton->SetButtonPosition({menu_position.x + buttonSpacing, menu_position.y + 200});
    smallTextButton->SetButtonColor(sf::Color(169, 173, 196));
    smallTextButton->UpdateButton();
    
    mediumTextButton->SetButtonPosition({menu_position.x + buttonSpacing * 2 + buttonWidth, menu_position.y + 200});
    mediumTextButton->SetButtonColor(sf::Color(169, 173, 196));
    mediumTextButton->UpdateButton();
    
    largeTextButton->SetButtonPosition({menu_position.x + buttonSpacing * 3 + buttonWidth * 2, menu_position.y + 200});
    largeTextButton->SetButtonColor(sf::Color(169, 173, 196));
    largeTextButton->UpdateButton();
    
    // Кнопка применения - в меню под кнопками размера
    float applyButtonWidth = 100;
    applyButton->SetButtonPosition({menu_position.x + (menuWidth - applyButtonWidth) / 2, menu_position.y + 250});
    applyButton->SetButtonColor(sf::Color(169, 173, 196));
    applyButton->UpdateButton();
}

void EditMenu::HideMenu() {
    isVisible = false;
    isTextEditing = false;
}

void EditMenu::DrawMenu(sf::RenderWindow& window) {
    if (!isVisible) return;
    
    // Рисуем фон
    window.draw(background);
    
    // Рисуем поле ввода текста
    window.draw(textInputBox);
    window.draw(inputText);
    
    // Рисуем курсор если редактируем текст
    if (isTextEditing) {
        static sf::Clock blinkClock;
        if (blinkClock.getElapsedTime().asSeconds() < 0.5f) {
            sf::RectangleShape cursor({2, 20});
            cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width + 2, 
                             inputText.getPosition().y + 2);
            cursor.setFillColor(sf::Color::Black);
            window.draw(cursor);
        }
        if (blinkClock.getElapsedTime().asSeconds() > 1.0f) {
            blinkClock.restart();
        }
    }
    
    // Рисуем цветовые круги
    for (auto& circle : colorCircles) {
        window.draw(circle);
    }
    
    // Рисуем кнопки
    smallTextButton->DrawButton(window);
    mediumTextButton->DrawButton(window);
    largeTextButton->DrawButton(window);
    applyButton->DrawButton(window);
    
    // Рисуем подписи
    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(14);
    label.setFillColor(sf::Color::Black);
    
    label.setString("Text:");
    label.setPosition(menu_position.x + 10, menu_position.y + 5);
    window.draw(label);
    
    label.setString("Color:");
    label.setPosition(menu_position.x + 10, menu_position.y + 65);
    window.draw(label);
    
    label.setString("Size:");
    label.setPosition(menu_position.x + 10, menu_position.y + 175);
    window.draw(label);
}

int EditMenu::HandleClick(sf::Vector2f mousePos) {
    if (!isVisible) return -1;
    
    // Проверяем клик по полю ввода текста
    if (textInputBox.getGlobalBounds().contains(mousePos)) {
        isTextEditing = true;
        return -2; // Специальный код для поля ввода
    }
    
    // Проверяем клики по цветовым кругам
    for (size_t i = 0; i < colorCircles.size(); ++i) {
        if (colorCircles[i].getGlobalBounds().contains(mousePos)) {
            selectedColor = colors[i];
            return 100 + static_cast<int>(i); // Коды 100-105 для цветов
        }
    }
    
    // Проверяем клики по кнопкам размера текста
    if (smallTextButton->IsMouseOnButton(mousePos)) {
        selectedTextSize = 16;
        return 200; // Код для маленького размера
    }
    if (mediumTextButton->IsMouseOnButton(mousePos)) {
        selectedTextSize = 24;
        return 201; // Код для среднего размера
    }
    if (largeTextButton->IsMouseOnButton(mousePos)) {
        selectedTextSize = 32;
        return 202; // Код для большого размера
    }
    
    // Проверяем клик по кнопке Apply
    if (applyButton->IsMouseOnButton(mousePos)) {
        isTextEditing = false;
        return 1; // Код для применения изменений
    }
    
    return -1;
}

void EditMenu::HandleTextInput(char c) {
    if (isTextEditing && c >= 32 && c < 127) { // Печатаемые символы
        currentText += c;
        inputText.setString(currentText);
    }
}

void EditMenu::HandleKeyPress(sf::Keyboard::Key key) {
    if (isTextEditing) {
        if (key == sf::Keyboard::BackSpace && !currentText.empty()) {
            currentText.pop_back();
            inputText.setString(currentText);
        } else if (key == sf::Keyboard::Enter) {
            isTextEditing = false;
        }
    }
}

bool EditMenu::IsMouseInMenu(sf::Vector2f mousePos) {
    if (!isVisible) return false;
    return background.getGlobalBounds().contains(mousePos);
}

void EditMenu::SetCurrentText(const std::string& text) {
    currentText = text;
    inputText.setString(currentText);
}

void EditMenu::SetSelectedColor(sf::Color color) {
    selectedColor = color;
}

void EditMenu::SetSelectedTextSize(unsigned int size) {
    selectedTextSize = size;
}