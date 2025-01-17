#include "ViewportController.h"

#include "Objects/Pawns/ViewportPawn.h"

void ViewportController::InitBaseInput()
{
    IComponent = new InputComponent();
    IComponent->BindKey(sf::Mouse::Right, {
           [this]() { bIsRightMouseButtonPressed = true; },
           [this]() { bIsRightMouseButtonPressed = false; }
    });
           
    
}
