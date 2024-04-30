#include "Bullet.h"
#include "GameManager.h"

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
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}