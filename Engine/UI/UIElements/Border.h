#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "UIElement.h"

class Border : public UIElement {
public:
    Border(const Vector2D& ScreenPosition, const Vector2D& Scale, const sf::Color& Color)
        : UIElement(ScreenPosition, Scale, Color) {
        Shape.setFillColor(Color);
    }

    void Draw(sf::RenderWindow& window) override {
        Shape.setPosition(sf::Vector2f(GetScreenPosition().X , GetScreenPosition().Y)); // Обновляем позицию перед отрисовкой
        Shape.setSize(sf::Vector2f(GetScale().X, GetScale().Y)); // Обновляем размер, если это необходимо
        window.draw(Shape);
    }

private:
    sf::RectangleShape Shape;
};