#pragma once
#include "Actor.h"
#include "Controller.h"
#include "Pointers/SmartPointer.h"

class Pawn : public Actor
{


protected:
    SmartPointer<Controller> controller;
    
};
