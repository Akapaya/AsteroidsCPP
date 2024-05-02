#include <SFML/Graphics.hpp>

class Botao {
public:
    Botao(float x, float y, float width, float height, std::string buttonText, std::string cost);

    void Draw(sf::RenderWindow& window);

    bool isClicked(sf::Event event) {
        int mouseX = event.mouseButton.x;
        int mouseY = event.mouseButton.y;
        int buttonPosX = shape.getPosition().x;
        int buttonPosY = shape.getPosition().y;
        int buttonxPosWidth = shape.getPosition().x + shape.getGlobalBounds().width;
        int buttonyPosHeight = shape.getPosition().y + shape.getGlobalBounds().height;

        if (mouseX < buttonxPosWidth && mouseX > buttonPosX && mouseY < buttonyPosHeight && mouseY > buttonPosY) {
            return true;
        }
        return false;
    }

private:
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;
    sf::Text costText;
};