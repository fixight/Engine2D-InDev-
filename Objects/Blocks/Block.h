#pragma once
#include "Objects/Actor.h"

class Block : public Actor
{
    void Tick(const float DeltaSeconds) override;

public:
    Block()
    {
        bMovable = false;
        if (!ObjectTexture.loadFromFile("Sprites/Test.png")) {
            std::cerr << "Ошибка загрузки текстуры фона!" << std::endl;
            return;
        }
    }
    
};
