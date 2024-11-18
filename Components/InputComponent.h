#pragma once
#include <functional>
#include <map>
#include <SFML/Window/Keyboard.hpp>

#include "Objects/Object.h"

class InputComponent : public Object 
{

public:
    InputComponent();

    void Tick(const float DeltaSeconds) override;

private:
    std::map<sf::Keyboard::Key, std::function<void()>> KeyBindings;

private:
    void ProcessInput();

public:
    void BindKey(sf::Keyboard::Key Key, std::function<void()> Action) {
        KeyBindings[Key] = Action;
    }
};
