#include "Global.h"
#include "Bullet.h"
#include "Player.h"
#include "GameManager.h"

Player :: Player() : Entity(sf::Vector2f(500, 500), 0.0f), array(sf::Quads, 4)
	{
		array[0].position = sf::Vector2f(60, 0);
		array[1].position = sf::Vector2f(-30, -20);
		array[2].position = sf::Vector2f(0, 0);
		array[3].position = sf::Vector2f(-30, 20);

		for (size_t i = 0; i < array.getVertexCount(); i++)
		{
			array[i].color = sf::Color::Yellow;
		}
	}

	void Player::Update(float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			angle -= turnSpeed * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			angle += turnSpeed * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			float radians = angle * (mPi / 180.0f);

			position.x += cos(radians) * movementSpeed * deltaTime;
			position.y += sin(radians) * movementSpeed * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			float radians = angle * (mPi / 180.0f);

			position.x -= cos(radians) * movementSpeed * deltaTime;
			position.y -= sin(radians) * movementSpeed * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			float radians = angle * (mPi / 180.0f);

			GameManager::InstanceBullets(position, sf::Vector2f(cos(radians), sin(radians)));
		}
	}

	void Player::Draw(sf::RenderWindow& window)  {
		sf::Transform transform;
		transform.translate(position);
		transform.rotate(angle);
		window.draw(array, transform);
	}

