#pragma once
#include "Engine/Camera.h"
#include "Engine/World.h"
#include "Objects/Actor.h"
#include "Pointers/SmartPointer.h"

class Controller;

class Pawn : public Actor
{

public:

    Pawn()
    {
        PawnCamera = World::GetWorld()->SpawnObject<Camera>(this->GetTransform()).Get();
        AttachActor(PawnCamera);
    }


    void Tick(const float DeltaSeconds) override;

protected:
    SmartPointer<Controller> controller;

    Camera* PawnCamera = nullptr;

public:
    Camera* GetCamera() { return PawnCamera; }
    
    
};
