#include "Actor.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace sf
{
    
}

Actor::Actor()
{
    
}

void Actor::Tick(const float DeltaSeconds)
{
    Object::Tick(DeltaSeconds);

    //if(PreviousPosition.X == 0.f && PreviousPosition.Y == 0.f) std::cout<<"Zero" << std::endl;

    Velocity = Location - PreviousPosition;

    PreviousPosition = Location;

   

    for (auto* child : Children) {
        child->UpdateLocalPosition();  
    }
    

    
}

void Actor::BeginPlay()
{
    Object::BeginPlay();

    PreviousPosition = Location;
}


void Actor::AttachActor(Actor* attached_actor)
{
    if(attached_actor == nullptr || attached_actor == this) return;

    attached_actor->LocalPosition = attached_actor->Location - Location;
    attached_actor->SetParent(this);

    Children.push_back(attached_actor);
}

void Actor::DrawActor(sf::RenderWindow* Window, Vector2D ScreenLocation)
{
    ObjectSprite.setTexture(ObjectTexture);
    ObjectSprite.setScale(0.1f , 0.1f);
    ObjectSprite.setPosition(sf::Vector2f(ScreenLocation.X , ScreenLocation.Y));
    Window->draw(ObjectSprite);
}

void Actor::UpdateLocalPosition()
{
    if(!Parent) return;

    Location = this->LocalPosition + Parent->Location;
}

bool Actor::LoadTexture(const std::string& FilePath)
{
    if (!ObjectTexture.loadFromFile(FilePath)) {
        std::cerr << "Ошибка при загрузке текстуры из файла: " << FilePath << std::endl;
        return false;
    }
    
    ObjectSprite.setTexture(ObjectTexture);
    
    return true;
}
