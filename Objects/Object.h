#pragma once
#include "ITickable.h"


class Object : ITickable
{

protected:
    Object();

    void Tick(const float DeltaSeconds) override;

protected:
    Object* Owner = nullptr;

    bool IsGarbage = false;
    
    bool CanTick = true;

protected:
    

public:
    void SetOwner(Object* NewOwner) {
        Owner = NewOwner;
    }

    void SetCanTick(const bool bCanTick){
        if(CanTick == true){}
    }

    void MarkAsGarbage() {IsGarbage = true;}

    
    
};
