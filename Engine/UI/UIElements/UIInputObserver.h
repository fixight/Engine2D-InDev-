#pragma once
#include <SFML/System/Vector2.hpp>

class IUIInputObserver {
public:
    virtual ~IUIInputObserver() = default;
    
    virtual void OnLeftMouseButtonPressed() = 0;
    virtual void OnRightMouseButtonPressed() = 0;
    virtual void OnMouseWheelScrolled(float delta) = 0;
    virtual void OnMouseMoved(const sf::Vector2f& position) = 0;
};
