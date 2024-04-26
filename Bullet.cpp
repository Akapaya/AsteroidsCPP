#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
	:shape(1.0f), direction(direction), Entity(position, 0.0f) {}

void Bullet::Update(float deltaTime)
{
	position += direction * bulletSpeed * deltaTime;
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}