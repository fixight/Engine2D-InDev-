#include "InputComponent.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine/UI/UIElements/UIInputObserverAdapter.h"

InputComponent::InputComponent()
{

    for (int key = sf::Keyboard::A; key != sf::Keyboard::KeyCount; ++key) {
        IsPressedStatus[static_cast<sf::Keyboard::Key>(key)] = false;
    }

    for (int button = sf::Mouse::Left; button != sf::Mouse::ButtonCount; ++button) {
        MousePressedStatus[static_cast<sf::Mouse::Button>(button)] = false;
    }
}

void InputComponent::Tick(const float DeltaSeconds)
{
    Object::Tick(DeltaSeconds);
    ProcessInput();
}

void InputComponent::HandleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        MouseWheelDelta = event.mouseWheelScroll.delta; 
        NotifyMouseWheelScrolled(MouseWheelDelta); 
    }
}

void InputComponent::ProcessInput()
{

    for (const auto& [Key, Action] : KeyBindings) {
        bool IsCurrentlyPressed = sf::Keyboard::isKeyPressed(Key);
        bool WasPreviouslyPressed = IsPressedStatus[Key];

        if (IsCurrentlyPressed) {
            Action.OnPressed(); 
        }

        if (!IsCurrentlyPressed && WasPreviouslyPressed) {
            Action.OnReleased(); 
        }

        IsPressedStatus[Key] = IsCurrentlyPressed;
    }
    
    for (const auto& [Button, Action] : MouseBindings) {
        bool IsCurrentlyPressed = sf::Mouse::isButtonPressed(Button);
        bool WasPreviouslyPressed = MousePressedStatus[Button];

        if (IsCurrentlyPressed) {
            Action.OnPressed(); 
        }

        if (!IsCurrentlyPressed && WasPreviouslyPressed) {
            Action.OnReleased(); 
        }

        MousePressedStatus[Button] = IsCurrentlyPressed;
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        NotifyLeftMouseButtonPressed();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        NotifyRightMouseButtonPressed();
    }
    
    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
    NotifyMouseMoved(mousePosition);
}

void InputComponent::NotifyLeftMouseButtonPressed() {
    for (auto observer : Observers) {
        observer->OnLeftMouseButtonPressed();
    }
}

void InputComponent::NotifyRightMouseButtonPressed() {
    for (auto observer : Observers) {
        observer->OnRightMouseButtonPressed();
    }
}

void InputComponent::NotifyMouseWheelScrolled(float delta) {
    for (auto observer : Observers) {
        observer->OnMouseWheelScrolled(delta);
    }

}

void InputComponent::NotifyMouseMoved(const sf::Vector2f& position) {
    for (auto observer : Observers) {
        observer->OnMouseMoved(position);
    }
}

void InputComponent::InitBasePlayerInput()
{
    BindKey(sf::Mouse::Left, {
        [this]() { OnLeftMouseButtonPressed(); }
    });

    BindKey(sf::Mouse::Right, {
        [this]() { OnRightMouseButtonPressed(); }
    });
}

void InputComponent::OnLeftMouseButtonPressed()
{
    std::cout << "Left mouse button pressed!" << std::endl;
}

void InputComponent::OnRightMouseButtonPressed()
{
    std::cout << "Right mouse button pressed!" << std::endl;
}