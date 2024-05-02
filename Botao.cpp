#include "Botao.h"

Botao::Botao(float x, float y, float width, float height, std::string buttonText, std::string cost) {
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    font.loadFromFile("Fonts/PoetsenOne.ttf");

    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + (width / 2) - (text.getGlobalBounds().width / 2), y + (height / 2) - (text.getGlobalBounds().height / 2));

    costText.setFont(font);
    costText.setString(cost);
    costText.setCharacterSize(12);
    costText.setFillColor(sf::Color::White);
    costText.setPosition(x + (width / 2) - (costText.getGlobalBounds().width / 2), y + height + 10);
}

void Botao::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(text);
    window.draw(costText);
}