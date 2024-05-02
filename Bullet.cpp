#include "Bullet.h"
#include "GameManager.h"
#include "Physics.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
	:shape(1.0f), direction(direction), Entity(position, 0.0f), lifeTime(bulletLife) {}

void Bullet::Update(float deltaTime)
{
	position += direction * bulletSpeed * deltaTime;

	lifeTime -= deltaTime;

	if (lifeTime <= 0.0f)
	{
		GameManager::toRemoveList.push_back(std::find(GameManager::entities.begin(), GameManager::entities.end(), this));
	}

	for (size_t i = 0; i < GameManager::entities.size(); i++)
	{
		if (typeid(*GameManager::entities[i]) == typeid(Asteroid))
		{
			Asteroid* asteroid = dynamic_cast<Asteroid*>(GameManager::entities[i]);
			sf::Transform transform = sf::Transform().translate(asteroid->position).rotate(asteroid->angle);

			if (physics::intersects(position,
				physics::GetTransformed(asteroid->GetVertexArray(),transform)))
			{
				lifeTime = 0.0f;
				GameManager::toRemoveList.push_back(std::find(GameManager::entities.begin(), GameManager::entities.end(), asteroid));
				GameManager::Score += 10;
			}
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}