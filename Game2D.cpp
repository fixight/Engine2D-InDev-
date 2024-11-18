#include <iostream>
#include <SFML/Graphics.hpp>
#include "Objects/Object.h"
#include "Engine/Camera.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Objects/Actor.h"


int main()
{
    

    Engine::GetEngine();

    
        
    Engine::GetEngine()->InitEngine();

    return 0;
    
}

