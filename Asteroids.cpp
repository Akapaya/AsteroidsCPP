#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameManager.h"
#include "Physics.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids",
        sf::Style::Close | sf::Style::Titlebar);

    sf::RenderWindow shopWindow(sf::VideoMode(500, 200), "Shop Asteroids",
        sf::Style::None | sf::Style::Titlebar);

    sf::Clock clock;

    GameManager gameManager;

    gameManager.Init();

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event e{ };
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
            else
            {
                
            }
        }

        window.clear();

        gameManager.Update(window, deltaTime);

        gameManager.UpdateShop(shopWindow, deltaTime);

        window.display();

        shopWindow.display();
    }
}