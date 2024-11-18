#include "Engine.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Camera.h"
#include "Renderer.h"
#include "World.h"
#include "Core/Vector2D.h"
#include "Objects/ITickable.h"

SmartPointer<Camera> NewCamera;

Engine* Engine::engine = nullptr;

void Engine::InitEngine()
{
    
    Renderer* renderer = new Renderer();

    SmartPointer<Controller> controller = SmartPointer<Controller>(new Controller());
    controller->InitPlayer();
    
    
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML Sprite Example");

    



    sf::Clock clock;
    
    sf::Time deltaTime;
    
    
    
    

    Transform CameraTransform;
    CameraTransform.Position = Vector2D(100.0f, 400.0f);
    CameraTransform.Scale = Vector2D(1.0f, 1.0f);
    CameraTransform.Rotation = 45.0f;

    if(!NewCamera.Get())
        NewCamera = World::GetWorld()->SpawnObject<class Camera>(CameraTransform);

    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    std::cout << "Нажата клавиша W" << std::endl;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Левая кнопка мыши нажата" << std::endl;
                }
            }
        }

        deltaTime = clock.restart();

        float deltaSeconds = deltaTime.asSeconds();

        window.clear(sf::Color::Black);
        Tick();
        renderer->Render(&window , NewCamera.Get());


        window.display();

        
    }
}

void Engine::BindTickable(ITickable* tickable)
{
    TickablesActors.push_back(tickable);
}

void Engine::UnbindTickable(ITickable* tickable)
{
    TickablesActors.erase(
        std::remove(TickablesActors.begin(), TickablesActors.end(), tickable), 
        TickablesActors.end()
    );
}

void Engine::Tick()
{
    sf::Clock clock;
    
    sf::Time deltaTime;

    deltaTime = clock.restart();

    float deltaSeconds = deltaTime.asSeconds();

    for (auto element : TickablesActors)
    {
        element->Tick(deltaSeconds);
    }

    
}
