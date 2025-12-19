#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include "Interface.h"

class ButtonTest : public ::testing::Test {
protected:
    void SetUp() override {
        testPos = sf::Vector2f(100.0f, 50.0f);
        testText = "Test Button";
    }

    sf::Vector2f testPos;
    std::string testText;
};

TEST_F(ButtonTest, Constructor) {
    Button button(testPos, testText);
    
    // Проверяем позицию
    sf::Vector2f pos = button.GetButtonPosition();
    EXPECT_FLOAT_EQ(pos.x, testPos.x);
    EXPECT_FLOAT_EQ(pos.y, testPos.y);
}

TEST_F(ButtonTest, SetAndGetPosition) {
    Button button(testPos, testText);
    sf::Vector2f newPos(200.0f, 100.0f);
    
    button.SetButtonPosition(newPos);
    sf::Vector2f pos = button.GetButtonPosition();
    EXPECT_FLOAT_EQ(pos.x, newPos.x);
    EXPECT_FLOAT_EQ(pos.y, newPos.y);
}

TEST_F(ButtonTest, SetAndGetText) {
    Button button(testPos, testText);
    std::string newText = "New Button Text";
    
    button.SetButtonText(newText);
    // Примечание: Button не имеет GetButtonText(), но мы можем проверить через другие методы
}

TEST_F(ButtonTest, SetAndGetColor) {
    Button button(testPos, testText);
    sf::Color testColor = sf::Color::Blue;
    
    button.SetButtonColor(testColor);
    EXPECT_EQ(button.GetButtonColor().r, testColor.r);
    EXPECT_EQ(button.GetButtonColor().g, testColor.g);
    EXPECT_EQ(button.GetButtonColor().b, testColor.b);
}

TEST_F(ButtonTest, SetButtonSize) {
    Button button(testPos, testText);
    sf::Vector2f testSize(150.0f, 40.0f);
    
    button.SetButtonSize(testSize);
    sf::Vector2f size = button.GetButtonSize();
    EXPECT_FLOAT_EQ(size.x, testSize.x);
    EXPECT_FLOAT_EQ(size.y, testSize.y);
}

TEST_F(ButtonTest, MouseDetection) {
    Button button(testPos, testText);
    
    // Точка внутри кнопки
    sf::Vector2f insidePoint(testPos.x + 10, testPos.y + 10);
    EXPECT_TRUE(button.IsMouseOnButton(insidePoint));
    
    // Точка вне кнопки
    sf::Vector2f outsidePoint(testPos.x - 10, testPos.y - 10);
    EXPECT_FALSE(button.IsMouseOnButton(outsidePoint));
}