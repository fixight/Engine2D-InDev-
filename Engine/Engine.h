#pragma once
#include <functional>
#include <vector>

class ITickable;

class Engine
{
public:
    static Engine* GetEngine() {
        if (engine == nullptr) {
            engine = new Engine();
        }
        return engine;
    }

    static Engine* engine;

    void InitEngine();

private:
    std::vector<ITickable*> TickablesActors;

public:
    void BindTickable(ITickable* tickable);

    void UnbindTickable(ITickable* tickable);

private:
    void Tick();
    
};
