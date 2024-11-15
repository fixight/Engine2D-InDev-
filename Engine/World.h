#pragma once
#include <vector>
#include "WeakPointer.h"

struct Transform;

//������ � ������������ ���������� , ������ ��� ������� ����(�� �� ������� ���) ��������� ��� ���������� � �������� ��������
class World
{
    static World* GetWorld() {
        if(Instance == nullptr)
        {
            Instance = new World();
            return Instance;
        }
        
        
        return Instance;
    }

private:
   

    World() {}

    ~World() {}

    World(const World&) = delete;

    World& operator=(const World&) = delete;


private:
    static World* Instance;


public:
    template<typename T>
    T* SpawnObject(Transform& InTransform);
    

private:
    //std::vector<WeakPointer> objects;

};




World* World::Instance = nullptr;

