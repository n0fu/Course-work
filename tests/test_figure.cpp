#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include "Figure.h"

class FigureTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаем окно для тестов
        window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Test");
    }

    void TearDown() override {
        window.reset();
    }

    std::unique_ptr<sf::RenderWindow> window;
};

TEST_F(FigureTest, DefaultConstructor) {
    Figure figure(*window);
    
    // Проверяем, что фигура создалась с базовыми параметрами
    EXPECT_EQ(figure.GetFigureText(), "New note...");
    EXPECT_EQ(figure.GetFigureTextSize(), 32);
}

TEST_F(FigureTest, ConstructorWithPosition) {
    sf::Vector2f testPos(100.0f, 200.0f);
    Figure figure(*window, testPos);
    
    // Проверяем позицию
    sf::Vector2f pos = figure.GetFigurePosition();
    EXPECT_FLOAT_EQ(pos.x, testPos.x);
    EXPECT_FLOAT_EQ(pos.y, testPos.y);
}

TEST_F(FigureTest, SetAndGetText) {
    Figure figure(*window);
    std::string testText = "Test Note";
    
    figure.SetFigureText(testText);
    EXPECT_EQ(figure.GetFigureText(), testText);
}

TEST_F(FigureTest, SetAndGetColor) {
    Figure figure(*window);
    sf::Color testColor = sf::Color::Red;
    
    figure.SetFigureColor(testColor);
    EXPECT_EQ(figure.GetFigureColor().r, testColor.r);
    EXPECT_EQ(figure.GetFigureColor().g, testColor.g);
    EXPECT_EQ(figure.GetFigureColor().b, testColor.b);
}

TEST_F(FigureTest, SetAndGetTextSize) {
    Figure figure(*window);
    unsigned int testSize = 30;
    
    figure.SetFigureTextSize(testSize);
    EXPECT_EQ(figure.GetFigureTextSize(), testSize);
}

TEST_F(FigureTest, SetAndGetPosition) {
    Figure figure(*window);
    sf::Vector2f testPos(150.0f, 250.0f);
    
    figure.SetFigurePosition(testPos);
    sf::Vector2f pos = figure.GetFigurePosition();
    EXPECT_FLOAT_EQ(pos.x, testPos.x);
    EXPECT_FLOAT_EQ(pos.y, testPos.y);
}

TEST_F(FigureTest, GetFigureCenter) {
    Figure figure(*window);
    sf::Vector2f pos = figure.GetFigurePosition();
    sf::Vector2f size = figure.GetFigureSize();
    sf::Vector2f center = figure.GetFigureCenter();
    
    EXPECT_FLOAT_EQ(center.x, pos.x + size.x / 2.0f);
    EXPECT_FLOAT_EQ(center.y, pos.y + size.y / 2.0f);
}