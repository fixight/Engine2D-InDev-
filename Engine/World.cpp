#include "World.h"

World* World::Instance = nullptr;
std::vector<SmartPointer<PlayerStart>> World::PlayerStarts;
SmartPointer<Controller> World::LocalController;
