#pragma once

class ITickable
{

public:
    virtual void Tick(const float DeltaSeconds) = 0;
    
};
