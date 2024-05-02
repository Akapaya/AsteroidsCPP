#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

constexpr float PlayerWidth = 50.0f;
constexpr float PlayerHeight = 40.0f;
constexpr float turnSpeed = 100.0f;

class Player : public Entity
{
public:
	static float shootDelay;
	static float movementSpeed;
	static float turnSpeed;

	Player();

	void Update(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;	

private:
	sf::VertexArray array;

	float shootTimer;
};

