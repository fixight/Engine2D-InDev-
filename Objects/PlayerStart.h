#pragma once
#include "Actor.h"

class PlayerStart : public Actor
{
public:
    PlayerStart()
    {
        Transform NewTransform;
        NewTransform.Position = Vector2D(100.0f, 200.0f); 
        NewTransform.Scale = Vector2D(1.0f, 1.0f);
        NewTransform.Rotation = 0.0f;
        SetTransform(NewTransform);
    }
};
