#pragma once
#include <SFML/System/Vector2.hpp>

#include "UIInputObserver.h"

class UIInputObserverAdapter : public IUIInputObserver {
public:
    void OnLeftMouseButtonPressed() override {}
    void OnRightMouseButtonPressed() override {}
    void OnMouseWheelScrolled(float delta) override {}
    void OnMouseMoved(const sf::Vector2f& position) override {}
};
