#include "World.h"

#include "Objects/Actor.h"

template <typename T>
Actor* SpawnObject(Transform& InTransform)
{
    
    static_assert(std::is_base_of<Actor, T>::value, "T must be derived from Actor");
    
    T* NewObject = new T();

    Actor* NewActor = static_cast<Actor*>(NewObject);
    
    //NewActor->


    
    return static_cast<Actor*>(NewObject);
}
