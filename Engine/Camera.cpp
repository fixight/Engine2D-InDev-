#include "Camera.h"


Vector2D Camera::ConvertWorldToScreen(const Vector2D& worldPosition, const Vector2D& cameraPosition, float screenWidth, float screenHeight, float scale) {
    Vector2D screenPosition;

    
    float relativeX = (worldPosition.X - cameraPosition.X) * scale;
    float relativeY = (worldPosition.Y - cameraPosition.Y) * scale;
    
    screenPosition.X = relativeX + screenWidth / 2.0f;
    screenPosition.Y = relativeY + screenHeight / 2.0f;

    return screenPosition;
}