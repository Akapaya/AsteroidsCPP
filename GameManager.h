#pragma once

#include "Bullet.h"
#include "Player.h"
#include "Asteroid.h"
#include "Entity.h"
#include <vector>
#include <list>

class GameManager
{
public:
	static size_t Score;	

	static std::vector<Entity*> entities;
	static std::list<std::vector<Entity*>::const_iterator> toRemoveList;
	static std::list<Entity*> toAddList;

	static sf::SoundBuffer soundShooterBuffer;
	static sf::Sound shootSound;

	static void Init();

	static void Start();	

	static void Update(sf::RenderWindow& window, float deltaTime);

	static void GameOver();

	static void InstanceBullets(sf::Vector2f position, sf::Vector2f direction)
	{
		toAddList.push_back(new Bullet(position, direction));
	}

private:
	static float asteroidSpawnTime;
	static sf::Text asteroidsText;
	static sf::Text playText;
	static sf::Text gameOverText;
	static sf::Text continueText;
	static sf::Text scoreText;
	static sf::Font font;

	static size_t highScore;
	static sf::Text highScoreText;
	
	static enum State {MENU, PLAYING, GAME_OVER} state;
	
};

