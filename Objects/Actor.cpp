#include "Actor.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace sf
{
    
}

Actor::Actor()
{
}


void Actor::DrawActor(sf::RenderWindow* Window, Vector2D ScreenLocation)
{
    ObjectSprite.setTexture(ObjectTexture);
    ObjectSprite.setScale(0.1f , 0.1f);
    ObjectSprite.setPosition(sf::Vector2f(ScreenLocation.X , ScreenLocation.Y));
    Window->draw(ObjectSprite);
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
