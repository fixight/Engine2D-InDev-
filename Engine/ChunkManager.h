#pragma once
#include <unordered_map>

#include "Camera.h"
#include "Chunk.h"

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        std::size_t h1 = std::hash<T1>{}(pair.first);
        std::size_t h2 = std::hash<T2>{}(pair.second);
        return h1 ^ (h2 << 1); 
    }
};

class ChunkManager {
public:

    static ChunkManager* GetChunkManager() {
        if (Instance == nullptr) {
            Instance = new ChunkManager(300);
        }
        return Instance;
    }

    static ChunkManager* Instance;

    std::unordered_map<std::pair<int, int>, Chunk, PairHash> Chunks;

    int ChunkSize;

    ChunkManager(int ChunkSize) : ChunkSize(ChunkSize) {}

    void AddObjectToChunk(Actor* actor);

    Chunk& GetOrCreateChunk(int X, int Y);
    
public:
    std::vector<Chunk*> GetVisibleChunks(const Vector2D& CameraPosition, int ViewRadiusInChunks);

    std::vector<Actor*> GetObjectsInVisibleChunks(const Vector2D& CameraPosition, int ViewRadiusInChunks);



    void RenderDebug(sf::RenderWindow& window , Camera* Camera);
        
    

    void RemoveChunk(int WorldX, int WorldY) {
        auto ChunkCoords = std::make_pair(WorldX / ChunkSize, WorldY / ChunkSize);
        Chunks.erase(ChunkCoords);
    }
};
