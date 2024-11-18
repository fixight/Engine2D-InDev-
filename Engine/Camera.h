#pragma once
#include "Core/Vector2D.h"
#include "Objects/Actor.h"


class Camera : public Actor
{

public:
    Camera()
    {
        IsVisible = false;
    }


protected:
    Vector2D CameraFOV= Vector2D(500, 500);

public:
    Vector2D ConvertWorldToScreen(const Vector2D& worldPosition, const Vector2D& cameraPosition, float screenWidth, float screenHeight, float scale = 1.0f);
};
