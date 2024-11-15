#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Object.h"
#include "Core/Transform.h"
#include "Core/Vector2D.h"


class  Actor : public Object
{

    sf::Sprite ObjectSprite;

    sf::Texture ObjectTexture;

protected:
    Object* Owner = nullptr;

protected:
    Vector2D Location = Vector2D(0.0f , 0.0f);

    Vector2D Scale = Vector2D(1.0f, 1.0f);

    float Rotation = 0.0f;

    Transform ActorTransform;


public:
    void SetObjectLocation(Vector2D& NewLocation) { Location = NewLocation; }

    void SetObjectScale(Vector2D& NewScale) { Scale = NewScale; }

    void SetObjectRotation(float& NewRotaton) { Rotation = NewRotaton; }
     
    void AddObjectOffset(Vector2D& Offset) { Location = Location + Offset; }

    //
    
    Vector2D& GetObjectLocation() { return Location; }

    Vector2D& GetObjectScale() { return Scale; }

    float& GetObjectRotation() { return Rotation; }

    void SetTrasform(Transform& NewTransform)
    {
        ActorTransform = NewTransform;
        this->Location = NewTransform.Position;
        this->Scale = NewTransform.Scale;
        this->Rotation = NewTransform.Rotation;
    }

protected:
    bool bHasCollision = true;

    bool bMovable = true;
    
};
