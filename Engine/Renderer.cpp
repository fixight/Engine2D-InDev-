#include "Renderer.h"

#include "Camera.h"
#include "World.h"

Renderer::Renderer()
{
}

void Renderer::Render(sf::RenderWindow* Window , Camera* Camera)
{
    
    if (!Camera) {
        std::cerr << "Active camera not found!" << std::endl;
        return;
    }
    
    Vector2D CameraPosition = Camera->GetObjectLocation();
    float ScreenWidth = 1024;
    float ScreenHeight = 768;
    
    for (auto Object : World::GetWorld()->GetAllActors())
    {
        if (!Object.Get() || !Object->GetIsVisible()) { 
            continue;
        }

        
        
        Vector2D WorldPosition = Object->GetObjectLocation();
        
        Vector2D ScreenPosition = Camera->ConvertWorldToScreen(WorldPosition, CameraPosition, ScreenWidth, ScreenHeight);

        std::cout << "Rendering object at: " << ScreenPosition.X << ", " << ScreenPosition.Y << std::endl;

        

        Object->DrawActor(Window, ScreenPosition);
    }
}
