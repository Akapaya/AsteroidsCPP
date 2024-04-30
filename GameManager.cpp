#include "GameManager.h"
#include "Asteroid.h"
#include "Player.h"

std::vector<Entity*> GameManager::entities{};
std::list<std::vector<Entity*>::const_iterator> GameManager::toRemoveList{};
std::list<Entity*> GameManager::toAddList{};

float GameManager::asteroidSpawnTime{};

void GameManager::Start()
{
	entities.push_back(new Player());

	asteroidSpawnTime = defaultAsteroidSpawnTime;
}

void GameManager::Update(sf::RenderWindow& window, float deltaTime)
{
	toAddList.clear();
	toRemoveList.clear();
	window.clear();

	asteroidSpawnTime -= deltaTime;

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(deltaTime);
		entities[i]->Draw(window);
	}

	for (const auto& it : toRemoveList)
	{
		delete* it;
		entities.erase(it);
	}

	for (auto& ptr : toAddList)
	{
		entities.push_back(ptr);
	}

	if (asteroidSpawnTime <= 0.0f)
	{
		entities.push_back(new Asteroid());
		asteroidSpawnTime = defaultAsteroidSpawnTime;
	}
}