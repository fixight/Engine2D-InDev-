﻿#include "Object.h"

#include <iostream>

#include "Engine/Engine.h"

Object::Object()
{
    if (CanTick && Engine::engine)
    {
        std::cout << "Object::Object()" << std::endl;
        Engine::engine->BindTickable(this);
    }

    
        

   
}

void Object::RegisterPropertiesBase()
{
    RegisterProperty(CanTick);
}

void Object::Tick(const float DeltaSeconds)
{
    
}

void Object::BeginPlay()
{
    
}


