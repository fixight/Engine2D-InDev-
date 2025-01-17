#pragma once
#include <set>
#include <unordered_set>
#include <vector>

#include "Objects/Actor.h"


enum class ChunkState {
    Active,
    Lazy,
    Frozen
};

class Chunk
{
public:
    std::unordered_set<Actor*> Objects;

    Chunk(int X , int Y) : X(X), Y(Y)
    {
        
    }

    Chunk()
    {
        
    }

private:
    int X;

    int Y;

public:
    int getX(){return X;}

    int getY(){return Y;}
    
};
