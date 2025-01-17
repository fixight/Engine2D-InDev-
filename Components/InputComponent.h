#pragma once
#include <functional>
#include <map>
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Objects/Object.h"

namespace sf
{
    class Event;
}

class IUIInputObserver;

struct KeyActions
{
    std::function<void()> OnPressed;
    std::function<void()> OnReleased = [](){};
};

class InputComponent : public Object 
{
public:
    InputComponent();

    void Tick(const float DeltaSeconds) override;
    void HandleEvent(const sf::Event& event); // Новый метод для обработки событий SFML

    void BindKey(sf::Keyboard::Key Key, KeyActions Action) {
        KeyBindings[Key] = Action;
    }
    
    void BindKey(sf::Mouse::Button Button, KeyActions Action) {
        MouseBindings[Button] = Action;
    }

    void Subscribe(IUIInputObserver* observer) {
        Observers.push_back(observer);
    }

    void Unsubscribe(IUIInputObserver* observer) {
        Observers.erase(std::remove(Observers.begin(), Observers.end(), observer), Observers.end());
    }

    void InitBasePlayerInput();

private:    
    std::map<sf::Keyboard::Key, bool> IsPressedStatus;
    std::map<sf::Keyboard::Key, KeyActions> KeyBindings;
    
    std::map<sf::Mouse::Button, bool> MousePressedStatus;
    std::map<sf::Mouse::Button, KeyActions> MouseBindings;

    std::vector<IUIInputObserver*> Observers;

    float MouseWheelDelta = 0.0f; 

private:
    void ProcessInput();
    void NotifyLeftMouseButtonPressed();
    void NotifyRightMouseButtonPressed();
    void NotifyMouseWheelScrolled(float delta);
    void NotifyMouseMoved(const sf::Vector2f& position);

    void OnLeftMouseButtonPressed();
    void OnRightMouseButtonPressed();
};