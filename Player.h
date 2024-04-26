#pragma once
#include "Entity.h"

constexpr float turnSpeed = 100.0f;
constexpr float movementSpeed = 100.0f;

class Player : public Entity
{
public:
	Player();

	void Update(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;

private:
	sf::VertexArray array;
};

