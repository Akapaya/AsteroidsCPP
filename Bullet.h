#pragma once
#include "Entity.h"

constexpr float bulletSpeed = 500.0f;
constexpr float bulletLife = 3.0f;

class Bullet : public Entity
{

public:
	Bullet(sf::Vector2f position, sf::Vector2f direction);

	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window) override;

private:
	sf::Vector2f direction;
	sf::CircleShape shape;
	float lifeTime;
};