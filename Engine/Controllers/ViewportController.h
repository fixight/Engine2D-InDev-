#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Objects/Pawns/Pawn.h"
#include "Controller.h"
#include "Components/InputComponent.h"

class ViewportController : public Controller
{
private:
    bool bIsRightMouseButtonPressed = false; 
    sf::Vector2i LastMousePosition;

    void InitBaseInput() override;


public:
    ViewportController()
    {
        
        
    }

protected:
    void Tick(const float DeltaSeconds) override
    {
        
        Controller::Tick(DeltaSeconds);

        std::cout<<"ViewportController::Tick"<<std::endl;

        if (bIsRightMouseButtonPressed)
        {
            UpdateCamera();
        }
    }

private:
    void OnRightMouseButton(bool bPressed)
    {
        bIsRightMouseButtonPressed = bPressed;

        
        if (bPressed)
        {
            LastMousePosition = sf::Mouse::getPosition();
        }
    }

    void UpdateCamera()
    {
        sf::Vector2i CurrentMousePosition = sf::Mouse::getPosition();
        sf::Vector2i Delta = CurrentMousePosition - LastMousePosition;

        

        if (ControlledPawn.Get())
        {
            
            Vector2D NewPosition(ControlledPawn->GetObjectLocation().X, ControlledPawn->GetObjectLocation().Y);

            NewPosition.X -= Delta.x * 0.5f; // Скорость перемещения по X
            NewPosition.Y -= Delta.y * 0.5f; // Скорость перемещения по Y

            ControlledPawn->SetObjectLocation(NewPosition);
        }

        // Обновляем последнюю позицию мыши
        LastMousePosition = CurrentMousePosition;
    }
};
