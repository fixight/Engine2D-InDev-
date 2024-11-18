#pragma once

#include <vector>


#include "Objects/Actor.h"
#include "Objects/Object.h"
#include "Core/Transform.h"
#include "Objects/Pawn.h"
#include "Objects/PlayerStart.h"
#include "Pointers/SmartPointer.h"


class PlayerStart;


class World : public Object
{
public:
    static World* GetWorld() {
        if (Instance == nullptr) {
            Instance = new World();
        }
        return Instance;
    }

    static World* Instance;

    template<typename T>
    SmartPointer<T> SpawnObject(Transform& InTransform);

    std::vector<SmartPointer<Actor>> GetAllActors(){return AllActors;}

private:
    World() {}
    ~World() {}
    World(const World&) = delete;
    World& operator=(const World&) = delete;

private:
    std::vector<SmartPointer<Actor>> AllActors;

    static std::vector<SmartPointer<PlayerStart>> PlayerStarts;


public:
    static SmartPointer<PlayerStart> GetPlayerStart(const int ID)
    {
        if(PlayerStarts.size() == 0)  return SmartPointer<PlayerStart>(new PlayerStart());

        if(PlayerStarts[ID].Get()) return PlayerStarts[ID];

        return SmartPointer<PlayerStart>(new PlayerStart());
    }
};





template <typename T>
SmartPointer<T> World::SpawnObject(Transform& InTransform) {
    static_assert(std::is_base_of<Actor, T>::value, "T must be derived from Actor");
    
    SmartPointer<T> NewObject = SmartPointer<T>(new T());
    
    T* NewActor = static_cast<T*>(NewObject.Get());
    NewActor->SetTransform(InTransform);
    NewActor->SetOwner(this);

    AllActors.push_back(SmartPointer<Actor>(NewObject.Get()));
    
    return NewObject;
}






