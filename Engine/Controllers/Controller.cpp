#include "Controller.h"
#include "Components/InputComponent.h"
#include <iostream>
#include "Objects/Pawns/Pawn.h"
#include "Engine/World.h"



void Controller::InitBaseInput()
{
    IComponent = new InputComponent();
    
    IComponent->BindKey(sf::Keyboard::W, {
    [this]() { this->MoveForward(); }, 
    });
    
    IComponent->BindKey(sf::Keyboard::S, {
        [this]() { this->MoveBackward(); }
    });

    IComponent->BindKey(sf::Keyboard::A, {
        [this]() { this->MoveLeft(); }
    });

    IComponent->BindKey(sf::Keyboard::D, {
        [this]() { this->MoveRight(); }
    });

    
}

void Controller::Tick(const float DeltaSeconds)
{
    Object::Tick(DeltaSeconds);
}

void Controller::MoveForward() {
    if (ControlledPawn.Get()) {
        ControlledPawn->AddObjectOffset(Vector2D(0.0f, -1.0f * 0.2f)); 
    }
}

void Controller::MoveBackward() {
    if (ControlledPawn.Get()) {
        ControlledPawn->AddObjectOffset(Vector2D(0.0f, 1.0f * 0.2f)); 
    }
}

void Controller::MoveLeft() {
    if (ControlledPawn.Get())
    {
        ControlledPawn->AddObjectOffset(Vector2D(-1.0f * 0.2f, 0.0f));
    }
}

void Controller::MoveRight() {
    if (ControlledPawn.Get()) {
        ControlledPawn->AddObjectOffset(Vector2D(1.0f * 0.2f, 0.0f)); 
    }
}