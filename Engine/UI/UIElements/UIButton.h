#pragma once
#include <functional>
#include <SFML/Window/Mouse.hpp>

#include "Border.h"

class UIButton : public Border
{
    using Border::Border;


    bool IsMouseOver(const sf::RectangleShape& shape, const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        
        sf::FloatRect bounds = shape.getGlobalBounds();
        
        return bounds.contains(worldPos);
    }

    
};
