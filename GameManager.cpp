#include "GameManager.h"
#include "Asteroid.h"
#include "Player.h"
#include <fstream>
#include "ShopWindow.h"
#include "Botao.h"

std::vector<Entity*> GameManager::entities{};
std::list<std::vector<Entity*>::const_iterator> GameManager::toRemoveList{};
std::list<Entity*> GameManager::toAddList{};

size_t GameManager::highScore{};
sf::Text GameManager::highScoreText{};
size_t GameManager::Score{};

size_t GameManager::Coins{};

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

bool isNoCurrencyEnough;
sf::Text ShopText;
sf::Text ErrorBuyText;
sf::Text ActuallyCoinsText;
Botao IncreaseRateFireBT(20.f, 100.f, 120.f, 50.f, "Increase Rate Fire", "100");
Botao IncreaseMoveSpeedBT(160.f, 100.f, 120.f, 50.f, "Increase Move Speed", "100");
Botao IncreaseTurnSpeedBT(300.f, 100.f, 120.f, 50.f, "Increase Turn Speed", "100");

void GameManager::Init()
{
	std::ifstream file("score.dat", std::ios::binary | std::ios::in);

	if (file.is_open())
	{
		file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
		file.close();
	}

	font.loadFromFile("Fonts/PoetsenOne.ttf");
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

	ActuallyCoinsText.setFont(font);
	ActuallyCoinsText.setPosition(sf::Vector2f(40, 20));
	ActuallyCoinsText.setCharacterSize(12);
	ActuallyCoinsText.setString("Coins: " + std::to_string(Coins));

	ShopText.setFont(font);
	ShopText.setPosition(sf::Vector2f(200, 20));
	ShopText.setCharacterSize(24);
	ShopText.setString("SHOP");

	ErrorBuyText.setFont(font);
	ErrorBuyText.setPosition(sf::Vector2f(40, 170));
	ErrorBuyText.setCharacterSize(12);
	ErrorBuyText.setFillColor(sf::Color::Red);
	ErrorBuyText.setString("Not Currency Enough");

	soundShooterBuffer.loadFromFile("Sounds/SpaceShoot.wav");
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
			Coins = 0;
			isNoCurrencyEnough = false;
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

void GameManager::UpdateShop(sf::RenderWindow& window, float deltaTime)
{
	window.clear();
	IncreaseRateFireBT.Draw(window);
	IncreaseMoveSpeedBT.Draw(window);
	IncreaseTurnSpeedBT.Draw(window);

	window.draw(ShopText);
	window.draw(ActuallyCoinsText);

	if (isNoCurrencyEnough == true)
	{
		window.draw(ErrorBuyText);
	}

	ActuallyCoinsText.setString("Coins: " + std::to_string(Coins));

	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::MouseButtonPressed) {
			if (IncreaseRateFireBT.isClicked(event)) {
				if (Player::shootDelay > 0 && Coins >= 100)
				{
					Player::shootDelay = Player::shootDelay - 0.001f;
					Coins -= 100;
					isNoCurrencyEnough = false;
				}
				else
				{
					isNoCurrencyEnough = true;
				}
			}

			if (IncreaseMoveSpeedBT.isClicked(event)) {
				if (Coins >= 100)
				{
					Player::movementSpeed = Player::movementSpeed + 20.0f;
					Coins -= 100;
					isNoCurrencyEnough = false;
				}
				else
				{
					isNoCurrencyEnough = true;
				}
			}

			if (IncreaseTurnSpeedBT.isClicked(event)) {
				if (Coins >= 100)
				{
					Player::turnSpeed = Player::turnSpeed + 20.0f;
					Coins -= 100;
					isNoCurrencyEnough = false;
				}
				else
				{
					isNoCurrencyEnough = true;
				}
			}
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
