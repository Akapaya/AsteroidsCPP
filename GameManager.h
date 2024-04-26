#pragma once

#include "Bullet.h"
#include "Player.h"
#include "Entity.h"
#include <vector>

class GameManager
{
public:
	static std::vector<Entity*> entities;

	void Start()
	{
		entities.push_back(new Player());
	}

	void Update(float deltaTime) {
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Update(deltaTime);
		}
	}

	void Draw(sf::RenderWindow& window) {
		for (size_t i = 0; i < entities.size(); i++)
		{
			entities[i]->Draw(window);
		}
	}

	static void InstanceBullets(sf::Vector2f position, sf::Vector2f direction)
	{
		entities.push_back(new Bullet(position, direction));
	}
};

