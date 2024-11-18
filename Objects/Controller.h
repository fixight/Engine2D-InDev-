#pragma once
#include "Object.h"
#include "Pointers/WeakPointer.h"

class InputComponent;
class Pawn;

class Controller : public Object  //Контоллер отвечает за управление игрвоком пешкой
{

protected:
    SmartPointer<Pawn> ControlledPawn;

    InputComponent* IComponent = nullptr;

public:
    void InitPlayer();

protected:
    void Tick(const float DeltaSeconds) override;

private:
    void MoveForward();
    void MoveBackward();
    void MoveRight();
    void MoveLeft();
    
};
