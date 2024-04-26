#pragma once
#include <vector>
#include "Entity.h"
#include "Player.h"

std::vector<Entity*> entities{};

class EntitiesManager
{
public:
	
};

void InsertEntity(Entity* entity)
{
	entities.push_back(new Player());
}