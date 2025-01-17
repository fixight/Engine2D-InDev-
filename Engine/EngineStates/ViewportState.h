#pragma once
#include <iostream>

#include "EngineState.h"

class ViewportState : public EngineState
{
public:
    void Tick(float DeltaTime) override
    {
        UpdateEditorScene(DeltaTime);
        RenderViewport();
    }

    void OnEnter() override
    {
        std::cout << "Switched to Viewport mode" << std::endl;
    }

    void OnExit() override
    {
        std::cout << "Exiting Viewport mode" << std::endl;
    }

private:
    void UpdateEditorScene(float DeltaTime)
    {
        
    }

    void RenderViewport()
    {
        
    }
};
