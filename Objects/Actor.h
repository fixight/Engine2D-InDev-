#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Object.h"
#include "Core/Transform.h"
#include "Core/Vector2D.h"

namespace sf
{
    class RenderWindow;
}

class Actor : public Object
{
public:
    Actor(const std::string& TexturePath)  {


        if (!LoadTexture(TexturePath)) {
            std::cerr << "Не удалось загрузить текстуру: " << TexturePath << std::endl;
        }
    }

    Actor();

    void RegisterPropertiesBase() override {
        Object::RegisterPropertiesBase();

        std::string LocationString = Location.ToString();
        RegisterProperty(LocationString);
    }


    void Tick(const float DeltaSeconds) override;

    void BeginPlay() override;

    sf::Sprite ObjectSprite;
    sf::Texture ObjectTexture;

protected:
    Object* Owner = nullptr;

    Actor* Parent = nullptr;

    std::vector<Actor*> Children;

    Vector2D Location = Vector2D(0.0f, 0.0f);

    Vector2D LocalPosition = Vector2D(0.0f, 0.0f);

    Vector2D Scale = Vector2D(0.0f, 0.0f);
    
    float Rotation = 0.0f;
    Transform ActorTransform;

    Vector2D PreviousPosition = Vector2D(0.0f, 0.0f);

public:
    Vector2D Velocity;


public:
    bool bHasCollision = true;
    bool bMovable = true;
    bool IsVisible = true;

public:
    bool GetIsVisible() { return IsVisible; }

public:
    void SetObjectLocation(const Vector2D& NewLocation)
    {
        Location = NewLocation;
    }

    Vector2D GetVelocity() { return Velocity; }

    void AttachActor(Actor* attached_actor);

    void SetObjectScale(const Vector2D& NewScale) {

        sf::Vector2u TextureSize = ObjectTexture.getSize();

        if (TextureSize.x == 0 || TextureSize.y == 0) {
            return;
        }

        float ScaleX = NewScale.X / TextureSize.x;
        float ScaleY = NewScale.Y / TextureSize.y;

        ObjectSprite.setScale(ScaleX, ScaleY);
    }

    void DrawActor(sf::RenderWindow* Window , Vector2D ScreenLocation);

    void UpdateLocalPosition();

    void SetParent(Actor* newParent) { Parent = newParent; }
    
    void SetObjectRotation(float NewRotation) { Rotation = NewRotation; }

    void AddObjectOffset(const Vector2D& Offset) { Location = Location + Offset; }

    Vector2D GetObjectLocation() const { return Location; }

    Vector2D GetObjectScale() const {
        sf::Vector2f scale = ObjectSprite.getScale();
        std::cout << "Sprite Scale: " << scale.x << ", " << scale.y << std::endl;
    
        float scaledWidth = scale.x * ObjectTexture.getSize().x;
        float scaledHeight = scale.y * ObjectTexture.getSize().y;
    
        return Vector2D(scaledWidth, scaledHeight);
    }

    float GetObjectRotation() const { return Rotation; }
    

    void SetSprite(const sf::Sprite& NewSprite) { ObjectSprite = NewSprite; }

    void SetObjectTexture(const sf::Texture& NewTexture) { ObjectTexture = NewTexture; }

    bool LoadTexture(const std::string& FilePath);

    void SetTransform(const Transform& NewTransform)
    {
        ActorTransform = NewTransform;
        Location = NewTransform.Position;
        SetObjectScale(NewTransform.Scale);
        Rotation = NewTransform.Rotation;
    }

    Transform GetTransform() { return ActorTransform; }

    
};
