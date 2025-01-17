#pragma once
#include "Objects/Object.h"
#include "Objects/Pawns/Pawn.h"
#include "Pointers/WeakPointer.h"

class InputComponent;


class Controller : public Object  //Контоллер отвечает за управление игрвоком пешкой
{

protected:
    SmartPointer<Pawn> ControlledPawn;

    InputComponent* IComponent = nullptr;

public:
    template<typename PawnClass>
    void InitPlayer()
    {
        Transform TempTransform = World::GetPlayerStart(0)->GetTransform();
        ControlledPawn = World::GetWorld()->SpawnObject<PawnClass>(TempTransform);
        ControlledPawn->LoadTexture("Sprites/Test.png");

        std::cout << "InitNewPawn" << std::endl;

        Vector2D Scale = ControlledPawn->GetObjectScale();
    
        InitBaseInput();
    }

    virtual void InitBaseInput();

    Pawn* GetControlledPawn(){return ControlledPawn.Get();}

public:
    InputComponent* GetInputComponent(){return IComponent;}

protected:
    void Tick(const float DeltaSeconds) override;

private:
    void MoveForward();
    void MoveBackward();
    void MoveRight();
    void MoveLeft();
    
};
