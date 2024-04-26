#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity(sf::Vector2f position, float angle)
		: position(position), angle(angle)
	{

	}

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	sf::Vector2f position;
	float angle;
};

