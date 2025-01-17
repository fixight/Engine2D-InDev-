#pragma once
#include <SFML/Graphics/Text.hpp>

#include "UIElement.h"

class UIText : public UIElement
{
public:
    UIText(Vector2D& ScreenPosition, Vector2D& Scale, sf::Color& Color, const std::string& text = "")
        : UIElement(ScreenPosition, Scale, Color), StringText(text) {
        Text.setPosition(ScreenPosition.X, ScreenPosition.Y);
        Text.setFillColor(Color);

        // Загрузка шрифта
        if (!font.loadFromFile("Fonts/arialmt.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }

        Text.setString(StringText);
        Text.setFont(font);
        Text.setCharacterSize(CharacterSize);
    }

    void SetCharacterSize(int CharSize)
    {
        CharacterSize = CharSize;
        Text.setCharacterSize(CharacterSize);
    }

    int GetCharacterSize()
    {
        return CharacterSize;
    }

    void Draw(sf::RenderWindow& window) override {
        window.draw(Text);
    }

    void SetText(const std::string& str)
    {
        StringText = str;
        Text.setString(StringText);  
    }

    std::string GetText()
    {
        return StringText;
    }

private:
    sf::String StringText;
    sf::Text Text;
    sf::Font font;  
    int CharacterSize = 40;
};

