#include <iostream>
#include <ostream>

#include "EngineState.h"

class SimulationState : public EngineState
{
public:
    void Tick(float DeltaTime) override
    {
        // Логика игры
        UpdateGameWorld(DeltaTime);
        RenderGame();
    }

    void OnEnter() override
    {
        std::cout << "Switched to Simulation mode" << std::endl;

        
        LoadActiveScene();
        StartActors();
    }

    void OnExit() override
    {
        std::cout << "Exiting Simulation mode" << std::endl;

        // Очистка состояния
        StopActors();
    }

private:
    void UpdateGameWorld(float DeltaTime)
    {
        // Логика игрового мира
    }

    void RenderGame()
    {
        // Финальный рендеринг сцены
    }

    void LoadActiveScene()
    {
        // Загрузка активной сцены
    }

    void StartActors()
    {
        // Вызов OnBeginPlay у всех объектов
    }

    void StopActors()
    {
        // Вызов OnEndPlay у всех объектов
    }
};
