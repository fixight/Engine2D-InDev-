#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Camera;

class Renderer
{

public:
    Renderer();

public:
    void Render(sf::RenderWindow* Window , Camera* Camera);
};

