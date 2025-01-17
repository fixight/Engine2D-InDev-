#include "ChunkManager.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Camera.h"
#include "Chunk.h"

ChunkManager* ChunkManager::Instance = nullptr;

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


void ChunkManager::AddObjectToChunk(Actor* actor)
{
    if (!actor)
    {
        std::cerr << "Error: actor is null!" << std::endl;
        return;
    }
    

    int chunkX = static_cast<int>(actor->GetObjectLocation().X) / ChunkSize;
    int chunkY = static_cast<int>(actor->GetObjectLocation().Y) / ChunkSize;

    if (Chunks.find(std::make_pair(chunkX, chunkY)) != Chunks.end()) {
        std::cout << "Chunk already exists: (" << chunkX << ", " << chunkY << ")\n";
    }

    Chunk& chunk = GetOrCreateChunk(chunkX , chunkY);
    chunk.Objects.insert(actor);

    //std::cout << "Object added to chunk (" << chunkX << ", " << chunkY << "). Total objects in chunk: " << chunk.Objects.size() << std::endl;

    //std::cout << "Object added to chunk (" << chunkX << ", " << chunkY << "). Total objects in chunk: " << chunk.Objects.size() << std::endl;
}


Chunk& ChunkManager::GetOrCreateChunk(int X, int Y)
{
    auto ChunkCoords = std::make_pair(X, Y);

    
    if (Chunks.find(ChunkCoords) == Chunks.end()) {
        std::cout<<"Creating new chunk on " << X << " " << Y << std::endl;
        Chunks[ChunkCoords] = Chunk(ChunkCoords.first, ChunkCoords.second);
    }
    
    return Chunks[ChunkCoords];
}

std::vector<Chunk*> ChunkManager::GetVisibleChunks(const Vector2D& CameraPosition, int ViewRadiusInChunks)
{
    
    std::vector<Chunk*> VisibleChunks;
    int ChunkX = static_cast<int>(CameraPosition.X) / ChunkSize;
    int ChunkY = static_cast<int>(CameraPosition.Y) / ChunkSize;
    

    for (int dx = -ViewRadiusInChunks; dx <= ViewRadiusInChunks; ++dx)
    {
        for (int dy = -ViewRadiusInChunks; dy <= ViewRadiusInChunks; ++dy)
        {
            
            auto ChunkCoords = std::make_pair(ChunkX + dx, ChunkY + dy);
           
            if (Chunks.find(ChunkCoords) != Chunks.end())
            {
                VisibleChunks.push_back(&Chunks[ChunkCoords]);
            }
        }
    }
    return VisibleChunks;
}

std::vector<Actor*> ChunkManager::GetObjectsInVisibleChunks(const Vector2D& CameraPosition, int ViewRadiusInChunks)
{
    std::vector<Actor*> VisibleObjects;
    auto VisibleChunks = GetVisibleChunks(CameraPosition, ViewRadiusInChunks);

    for (auto* Chunk : VisibleChunks)
    {
        for (auto* Object : Chunk->Objects)
        {
            if(Object->IsVisible)
                VisibleObjects.push_back(Object);
        }
    }
    return VisibleObjects;
}

void ChunkManager::RenderDebug(sf::RenderWindow& window , Camera* camera) {
    
    for (auto& pair : Chunks)
    {
        auto& chunk = pair.second;

        
       
        float globalLeft = chunk.getX() * ChunkSize;
        float globalTop = chunk.getY() * ChunkSize;
        
        Vector2D screenChunkPosition = camera->ConvertWorldToScreen(
            Vector2D(globalLeft, globalTop),
            camera->GetObjectLocation(),
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)
        );

        sf::RectangleShape rect(sf::Vector2f(static_cast<float>(ChunkSize), static_cast<float>(ChunkSize)));
        rect.setPosition(screenChunkPosition.X, screenChunkPosition.Y);
        rect.setFillColor(sf::Color(0, 0, 0, 0));  // Прозрачный фон
        rect.setOutlineColor(sf::Color(0, 255, 0));  // Для отладки: зелёная рамка
        rect.setOutlineThickness(1.f);
        window.draw(rect);
        
        for (auto* actor : chunk.Objects) {
            Vector2D screenActorPosition = camera->ConvertWorldToScreen(
                actor->GetObjectLocation(),
                camera->GetObjectLocation(),
                static_cast<float>(window.getSize().x),
                static_cast<float>(window.getSize().y)
            );
            
            sf::Vector2f textureSize = sf::Vector2f(actor->GetObjectScale().X, actor->GetObjectScale().Y);
            float actorRadius = 10.0f;
            sf::CircleShape actorShape(actorRadius);
            actorShape.setPosition(
                screenActorPosition.X + (textureSize.x / 2.0f),
                screenActorPosition.Y + (textureSize.y / 2.0f)
            );
            actorShape.setFillColor(sf::Color::Red);
            window.draw(actorShape);
        }
        
        sf::Font font;
        if (!font.loadFromFile("Fonts/arialmt.ttf")) { 
            std::cerr << "Error loading font!" << std::endl;
            return;
        }
        
        sf::Text chunkObjectCount;
        chunkObjectCount.setFont(font);
        chunkObjectCount.setString(std::to_string(chunk.Objects.size()));  
        chunkObjectCount.setCharacterSize(22); 
        chunkObjectCount.setFillColor(sf::Color::Red);  
        chunkObjectCount.setPosition(screenChunkPosition.X + 2, screenChunkPosition.Y + 2);  

        window.draw(chunkObjectCount);
    }
}
