#include "Global.h"
#include "Bullet.h"
#include "Player.h"
#include "GameManager.h"
#include "Physics.h"

float Player::shootDelay{};
float Player::movementSpeed{};
float Player::turnSpeed{};

Player :: Player() : Entity(sf::Vector2f(500, 500), 0.0f), array(sf::LinesStrip, 5), shootTimer()
	{
		array[0].position = sf::Vector2f(60, 0);
		array[1].position = sf::Vector2f(-30, -20);
		array[2].position = sf::Vector2f(0, 0);
		array[3].position = sf::Vector2f(-30, 20);
		array[4].position = array[0].position;

		for (size_t i = 0; i < array.getVertexCount(); i++)
		{
			array[i].color = sf::Color::Yellow;
		}

		movementSpeed = 100.0f;
		turnSpeed = 100.0f;
		shootDelay = 0.2f;
	}

	void Player::Update(float deltaTime)
	{
		shootTimer -= deltaTime;
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
			
			position.x = std::min(std::max(position.x, PlayerWidth / 2.0f), ScreenWidth - PlayerWidth / 2.0f);

			position.y = std::min(std::max(position.y, PlayerHeight / 2.0f), ScreenHeight - PlayerHeight / 2.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			float radians = angle * (mPi / 180.0f);

			position.x -= cos(radians) * movementSpeed * deltaTime;
			position.y -= sin(radians) * movementSpeed * deltaTime;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f)
		{
			if (shootDelay > 0.05f)
			{
				GameManager::shootSound.play();
			}
			shootTimer = shootDelay;
			float radians = angle * (mPi / 180.0f);

			GameManager::InstanceBullets(position, sf::Vector2f(cos(radians), sin(radians)));
		}

		sf::Transform playerTransform = sf::Transform().translate(position).rotate(angle);

		for (size_t i = 0; i < GameManager::entities.size(); i++)
		{
			if (typeid(*GameManager::entities[i]) == typeid(Asteroid))
			{
				Asteroid* asteroid = dynamic_cast<Asteroid*>(GameManager::entities[i]);
				sf::Transform asteroidTransform = sf::Transform().translate(asteroid->position).rotate(asteroid->angle);

				if (physics::intersects(physics::GetTransformed(array, playerTransform),
					physics::GetTransformed(asteroid->GetVertexArray(), asteroidTransform)))
				{
					GameManager::GameOver();
				}
			}
		}
	}

	void Player::Draw(sf::RenderWindow& window)  {
		sf::Transform transform;
		transform.translate(position);
		transform.rotate(angle);
		window.draw(array, transform);
	}

