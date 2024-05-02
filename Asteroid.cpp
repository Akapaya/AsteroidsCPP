#include "Global.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "GameManager.h"

Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position) 
	: Entity(sf::Vector2f(900, 300), 0.0f), direction(direction), array(sf::LinesStrip, 12)
{
	array[0].position = sf::Vector2f(-20, 20);
	array[1].position = sf::Vector2f(-25, 5);
	array[2].position = sf::Vector2f(-5, -10);
	array[3].position = sf::Vector2f(-10, -20);
	array[4].position = sf::Vector2f(5, -20);
	array[5].position = sf::Vector2f(20, -10);
	array[6].position = sf::Vector2f(20, -5);
	array[7].position = sf::Vector2f(0, 0);
	array[8].position = sf::Vector2f(20, 10);
	array[9].position = sf::Vector2f(10, 20);
	array[10].position = sf::Vector2f(0, 15);
	array[11].position = array[0].position;

	for (size_t i = 0; i < array.getVertexCount(); i++)
	{
		array[i].color = sf::Color::Yellow;
	}
}

void Asteroid::Update(float deltaTime)
{
	position += direction * asteroidSpeed * deltaTime;
	angle += asteroidSpin * deltaTime;

	if (position.x <AsteroidWidth /2.0f)
	{
		direction.x = abs(direction.x);
	}
	else
	{
		if (position.x > ScreenWidth - AsteroidWidth / 2.0f)
		{
			direction.x = -abs(direction.x);
		}
	}

	if (position.y < AsteroidHeight / 2.0f)
	{
		direction.y = abs(direction.y);
	}
	else
	{
		if (position.y > ScreenHeight - AsteroidHeight / 2.0f)
		{
			direction.y = -abs(direction.y);
		}
	}
}

void Asteroid::Draw(sf::RenderWindow& window) {
	sf::Transform transform;
	transform.translate(position);
	transform.rotate(angle);
	window.draw(array, transform);
}

const sf::VertexArray& Asteroid::GetVertexArray() const
{
	return array;
}

sf::Vector2f Asteroid::GetRandomDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 2.0f * mPi);

	float angle = dist(gen);
	return sf::Vector2f(cos(angle), sin(angle));
}

sf::Vector2f Asteroid::GetRandomPosition()
{
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> xAxis(AsteroidWidth / 2.0f, ScreenWidth - AsteroidWidth / 2.0f);

		std::uniform_real_distribution<float> yAxis(AsteroidHeight / 2.0f, ScreenHeight - AsteroidHeight / 2.0f);

		return sf::Vector2f(xAxis(gen), yAxis(gen));
	}
}

