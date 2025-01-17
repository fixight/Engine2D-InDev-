#pragma once
#include <vector>

#include "Objects/Actor.h"

class CollisionSystem
{
public:
    CollisionSystem()
    {
        
    }

    void CheckCollisions(const std::vector<Actor*>& actors)
    {
        
        for (size_t i = 0; i < actors.size(); ++i)
        {
            for (size_t j = i + 1; j < actors.size(); ++j)
            {
                if (IsColliding(actors[i], actors[j]))
                {
                    HandleCollision(actors[i], actors[j]);
                }
            }
        }
    }

    bool IsColliding(const Actor* A, const Actor* B)
    {

        Vector2D locationA = A->GetObjectLocation();
        Vector2D locationB = B->GetObjectLocation();
        
        auto PosA = A->GetObjectLocation();
        auto PosB = B->GetObjectLocation();

        auto ScaleA = A->GetObjectScale();
        auto ScaleB = B->GetObjectScale();

        return (PosA.X < PosB.X + ScaleB.X && PosA.X + ScaleA.X > PosB.X &&
                PosA.Y < PosB.Y + ScaleB.Y && PosA.Y + ScaleA.Y > PosB.Y);
    }

    void HandleCollision(Actor* A, Actor* B)
{
    std::cout << "HandleCollision between " << typeid(*A).name() 
              << " and " << typeid(*B).name() << std::endl;

    Vector2D locationA = A->GetObjectLocation();
    Vector2D locationB = B->GetObjectLocation();

    Vector2D halfSizeA = A->GetObjectScale() * 0.5f;
    Vector2D halfSizeB = B->GetObjectScale() * 0.5f;

    // Проверка размеров
    if (halfSizeA.X <= 0 || halfSizeA.Y <= 0 || halfSizeB.X <= 0 || halfSizeB.Y <= 0) {
        std::cout << "Invalid object sizes.\n";
        return;
    }

    Vector2D delta = locationA - locationB;

    float overlapX = halfSizeA.X + halfSizeB.X - fabs(delta.X);
    float overlapY = halfSizeA.Y + halfSizeB.Y - fabs(delta.Y);


    if (overlapX <= 0 || overlapY <= 0) {
        std::cout << "No collision detected.\n";
        return;
    }


    float maxShift = 50.0f; 

    if (overlapX < overlapY) {
        float shiftX = fmin(overlapX * 0.5f, maxShift);

        if (A->bMovable && B->bMovable) {
            if (delta.X > 0) {
                locationA.X += shiftX;
                locationB.X -= shiftX;
            } else {
                locationA.X -= shiftX;
                locationB.X += shiftX;
            }
        } else if (A->bMovable) {
            if (delta.X > 0) {
                locationA.X += shiftX * 2; 
            } else {
                locationA.X -= shiftX * 2;
            }
        } else if (B->bMovable) {
            if (delta.X > 0) {
                locationB.X -= shiftX * 2;
            } else {
                locationB.X += shiftX * 2;
            }
        }
    } else {
        float shiftY = fmin(overlapY * 0.5f, maxShift);

        if (A->bMovable && B->bMovable) {
            if (delta.Y > 0) {
                locationA.Y += shiftY;
                locationB.Y -= shiftY;
            } else {
                locationA.Y -= shiftY;
                locationB.Y += shiftY;
            }
        } else if (A->bMovable) {
            if (delta.Y > 0) {
                locationA.Y += shiftY * 2;
            } else {
                locationA.Y -= shiftY * 2;
            }
        } else if (B->bMovable) {
            if (delta.Y > 0) {
                locationB.Y -= shiftY * 2;
            } else {
                locationB.Y += shiftY * 2;
            }
        }
    }
        
    if (A->bMovable) {
        A->SetObjectLocation(locationA);
    }
    if (B->bMovable) {
        B->SetObjectLocation(locationB);
    }
}


};
