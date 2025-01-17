#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "UIInputObserverAdapter.h"
#include "Components/InputComponent.h"
#include "Core/Vector2D.h"
#include "Engine/World.h"
#include "Engine/Controllers/Controller.h"

class UIElement : public UIInputObserverAdapter {
public:
    UIElement(const Vector2D& ScreenPosition,const Vector2D& Scale , const sf::Color& Color)
        : ScreenPosition(ScreenPosition), Scale(Scale) , Color(Color)
    {
        World::GetWorld()->GetLocalController()->GetInputComponent()->Subscribe(this);
    }

    UIElement() = default;

    ~UIElement() = default;


    void SetScreenPosition(const Vector2D& position) {
        ScreenPosition = position;
    }

    void SetScale(const Vector2D& scale) {
        Scale = scale;
    }
    
    Vector2D GetScreenPosition() const {
        return ScreenPosition;
    }

    Vector2D GetScale() const {
        return Scale;
    }

    void SetColor(const sf::Color& color)
    {
        Color = color;
    }

    sf::Color GetColor()
    {
        return Color;
    }


protected:
    Vector2D ScreenPosition;
    Vector2D Scale;
    sf::Color Color = sf::Color::White;

public:
    virtual void Draw(sf::RenderWindow& window);
};
