#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>
#include <unordered_map>

constexpr float PlayerWidth = 50.0f;
constexpr float PlayerHeight = 40.0f;
constexpr float turnSpeed = 100.0f;
constexpr float movementSpeed = 100.0f;
constexpr float shootDelay = 0.2f;

class Player : public Entity
{
public:
	Player();

	void Update(float deltaTime) override;

	void Draw(sf::RenderWindow& window) override;	

private:
	sf::VertexArray array;

	float shootTimer;
};

