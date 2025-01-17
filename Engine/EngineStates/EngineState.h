#pragma once


class EngineState
{
public:
    virtual ~EngineState() = default;

    virtual void Tick(float DeltaTime) = 0;       // Логика, выполняемая каждый кадр
    virtual void OnEnter() = 0;                   // Логика при активации режима
    virtual void OnExit() = 0;                    // Логика при смене режима
};