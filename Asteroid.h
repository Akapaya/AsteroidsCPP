#pragma once
#include "Entity.h"
#include "Global.h"
#include <random>

constexpr float AsteroidWidth = 90.0f;
constexpr float AsteroidHeight = 80.0f;

constexpr float asteroidSpeed = 50.0f;
constexpr float asteroidSpin = 50.0f;

constexpr float defaultAsteroidSpawnTime = 2.0f;

class Asteroid : public Entity
{
public:
	Asteroid(sf::Vector2f direction = Asteroid::GetRandomDirection(), sf::Vector2f position = GetRandomPosition());

	void Update(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;
	const sf::VertexArray& GetVertexArray() const;

	static sf::Vector2f GetRandomDirection();	

	static sf::Vector2f GetRandomPosition();	

private:
	sf::VertexArray array;
	sf::Vector2f direction;
};

