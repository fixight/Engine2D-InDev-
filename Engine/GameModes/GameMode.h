#pragma once
#include "Objects/Pawns/Pawn.h"
#include "Engine/Controllers/Controller.h"


class GameMode
{
protected:
    Controller* PlayerController = nullptr;
    Pawn* PlayerPawn = nullptr;
    
public:
    virtual ~GameMode() 
    {
        delete PlayerController;
        delete PlayerPawn;
    }

    virtual void Init() = 0;              // Инициализация игрового режима

    virtual void Tick(float DeltaTime) = 0; // Основной игровой цикл

    virtual void Shutdown() = 0;         // Завершение игрового режима

    Controller* GetPlayerController() const { return PlayerController; }
    Pawn* GetPlayerPawn() const { return PlayerPawn; }
};
