#include "Engine.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Camera.h"
#include "Renderer.h"
#include "World.h"
#include "Collision/CollisionSystem.h"
#include "Controllers/Controller.h"
#include "Controllers/ViewportController.h"
#include "Core/Vector2D.h"
#include "Objects/ITickable.h"
#include "Objects/Blocks/Block.h"
#include "UI/UIElements/Border.h"
#include "UI/UIElements/UISizeBox.h"
#include "UI/UIElements/UIText.h"

//SmartPointer<Camera> NewCamera;

Engine* Engine::engine = nullptr;

void Engine::InitEngine()
{
    ChunkManager* chunk_manager = new ChunkManager(1000);
    CollisionSystem* collision_system = new CollisionSystem();
    Renderer* renderer = new Renderer();

    SmartPointer<Controller> controller = SmartPointer<Controller>(new Controller());
    controller->InitPlayer<Pawn>();
    World::GetWorld()->SetLocalController(controller);

    
    
    
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML Sprite Example");

    

    sf::Clock clock;
    
    sf::Time deltaTime;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Sprites/Back.png")) {
        std::cerr << "Ошибка загрузки текстуры фона!" << std::endl;
        return;
    }

    
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);


    
    float scaleX = window.getSize().x / static_cast<float>(backgroundTexture.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(backgroundTexture.getSize().y);
    backgroundSprite.setScale(scaleX, scaleY);
    
    

    Transform CameraTransform;
    CameraTransform.Position = Vector2D(100.0f, 400.0f);
    CameraTransform.Scale = Vector2D(100.0f, 1.0f);
    CameraTransform.Rotation = 45.0f;

    Transform GrassTransform;
    GrassTransform.Position = Vector2D(200.0f, 0.0f);
    GrassTransform.Scale = Vector2D(100.0f, 1.0f);
    GrassTransform.Rotation = 45.0f;

    SmartPointer<Block> NewBlock = World::GetWorld()->SpawnObject<Block>(GrassTransform);



    Vector2D Position(50.0f, 50.0f);
    Vector2D Scale(100.0f, 100.0f); // Уменьшаем масштаб Border
    sf::Color color = sf::Color::Black;

    std::shared_ptr<UIElement> NewBorder = std::make_shared<Border>(Position, Scale, color);
    std::shared_ptr<UIElement> NewBorder1 = std::make_shared<Border>(Position, Scale, color);
    std::shared_ptr<UIElement> NewBorder2 = std::make_shared<Border>(Position, Scale, color);

    Vector2D sizeBoxScale(350.0f, 350.0f); // Увеличиваем масштаб SizeBox, чтобы вместить Border
    SizeBox* NewSizeBox = new SizeBox(Position, sizeBoxScale);
    NewSizeBox->SetColor(sf::Color::White);
    NewSizeBox->SetAutoFill(true);
    NewSizeBox->SetPadding(10);
    NewSizeBox->SetGridSize(2, 2); // Размещаем в сетке 2x2


    NewSizeBox->AddChild(NewBorder);
    NewSizeBox->AddChild(NewBorder1);
    NewSizeBox->AddChild(NewBorder2);
     
    

    //if(!NewCamera.Get())
        //NewCamera = World::GetWorld()->SpawnObject<class Camera>(CameraTransform);


    for (auto element : World::GetWorld()->GetAllActors())
    {
        element->BeginPlay();
    }
     

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  
            }

        }

        window.clear();
        window.draw(backgroundSprite);
        

        deltaTime = clock.restart();

        float deltaSeconds = deltaTime.asSeconds();

       
        Tick();

        
        
        collision_system->CheckCollisions( ChunkManager::GetChunkManager()-> GetObjectsInVisibleChunks(controller->GetControlledPawn()->GetCamera()->GetObjectLocation() , 3 ));
        
        renderer->Render(&window , controller->GetControlledPawn()->GetCamera());

        ChunkManager::GetChunkManager()->RenderDebug(window , controller->GetControlledPawn()->GetCamera());

        NewSizeBox->Draw(window);
        
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
