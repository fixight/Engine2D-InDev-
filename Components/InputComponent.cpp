#include "InputComponent.h"

#include <iostream>

InputComponent::InputComponent()
{
    BindKey(sf::Keyboard::W, []() { std::cout << "Moving Forward" << std::endl; });
    BindKey(sf::Keyboard::A, []() { std::cout << "Moving Left" << std::endl; });
    BindKey(sf::Keyboard::S, []() { std::cout << "Moving Backward" << std::endl; });
    BindKey(sf::Keyboard::D, []() { std::cout << "Moving Right" << std::endl; });
}

void InputComponent::Tick(const float DeltaSeconds)
{
    Object::Tick(DeltaSeconds);

    ProcessInput();
    
}

void InputComponent::ProcessInput()
{
    for (const auto& Binding : KeyBindings) {
        if (sf::Keyboard::isKeyPressed(Binding.first)) {
            Binding.second(); 
        }
    }
}
