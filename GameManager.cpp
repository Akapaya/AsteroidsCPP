#include "GameManager.h"
#include "Asteroid.h"
#include "Player.h"
#include <fstream>

std::vector<Entity*> GameManager::entities{};
std::list<std::vector<Entity*>::const_iterator> GameManager::toRemoveList{};
std::list<Entity*> GameManager::toAddList{};

size_t GameManager::highScore{};
sf::Text GameManager::highScoreText{};
size_t GameManager::Score{};
float GameManager::asteroidSpawnTime{};
GameManager::State GameManager::state;

sf::SoundBuffer GameManager::soundShooterBuffer{};
sf::Sound GameManager::shootSound{};

sf::Text GameManager::asteroidsText{};
sf::Text GameManager::playText{};
sf::Text GameManager::gameOverText{};
sf::Text GameManager::continueText{};
sf::Text GameManager::scoreText{};
sf::Font GameManager::font{};

void GameManager::Init()
{
	std::ifstream file("score.dat", std::ios::binary | std::ios::in);

	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
		file.close();
	}

	font.loadFromFile("PoetsenOne.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(30, 20));
	scoreText.setCharacterSize(40);

	gameOverText.setFont(font);
	gameOverText.setPosition(sf::Vector2f(250, 350));
	gameOverText.setCharacterSize(128);
	gameOverText.setString("Game Over!");

	continueText.setFont(font);
	continueText.setPosition(sf::Vector2f(450, 550));
	continueText.setCharacterSize(24);
	continueText.setString("Press Enter to continue...?");

	asteroidsText.setFont(font);
	asteroidsText.setPosition(sf::Vector2f(280, 350));
	asteroidsText.setCharacterSize(128);
	asteroidsText.setString("Asteroids");

	playText.setFont(font);
	playText.setPosition(sf::Vector2f(450, 550));
	playText.setCharacterSize(24);
	playText.setString("Press Enter to play...");

	highScoreText.setFont(font);
	highScoreText.setPosition(sf::Vector2f(40, 20));
	highScoreText.setCharacterSize(48);
	highScoreText.setString("High Score: " + std::to_string(highScore));

	soundShooterBuffer.loadFromFile("SpaceShoot.wav");
	shootSound.setBuffer(soundShooterBuffer);

	state = MENU;
}

void GameManager::Start()
{
	state = PLAYING;

	entities.push_back(new Player());

	asteroidSpawnTime = defaultAsteroidSpawnTime;	
}

void GameManager::Update(sf::RenderWindow& window, float deltaTime)
{	
	window.clear();

	if (state == MENU)
	{
		window.draw(highScoreText);
		window.draw(asteroidsText);
		window.draw(playText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			Score = 0;
			Start();
		}
		return;
	}

	toAddList.clear();
	toRemoveList.clear();

	asteroidSpawnTime -= deltaTime;

	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(deltaTime);
		entities[i]->Draw(window);
	}

	for (const auto& it : toRemoveList)
	{
		delete* it;
		entities.erase(it);
	}

	for (auto& ptr : toAddList)
	{
		entities.push_back(ptr);
	}

	if (asteroidSpawnTime <= 0.0f)
	{
		entities.push_back(new Asteroid());
		asteroidSpawnTime = defaultAsteroidSpawnTime;
	}

	scoreText.setString(std::to_string(Score));
	window.draw(scoreText);

	if (state == GAME_OVER)
	{
		entities.clear();
		window.draw(gameOverText);
		window.draw(continueText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			Score = 0;
			Start();
		}
	}
}

void GameManager::GameOver()
{
	if (Score > highScore)
	{
		highScore = Score;
		std::ofstream file("score.dat", std::ios::binary | std::ios::out);
		if (file.is_open())
		{
			file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
			file.close();
		}
		else
		{
			printf("Failed to write highscore");
		}

		highScoreText.setString("High Score: " + std::to_string(highScore));
	}

	state = GAME_OVER;
}
