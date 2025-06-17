#include "card.h"

Card::Card(const char* path, float x, float y, int id) : id(id), isShown(false) {
	loadTexture(path);
	sprite.setPosition(x, y);
}

// SETTERS
void Card::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// GETTERS
bool Card::isHovered(const sf::Vector2f& mousePos) const {
    return sprite.getGlobalBounds().contains(mousePos);
}

void Card::loadTexture(const char* path) {
    if (!frontTexture.loadFromFile(path)) {
        std::cout << "Error loading asset"; // Error loading file
    }

    if (!backTexture.loadFromFile("Assets/card0.png")) {
		std::cout << "Error loading asset"; // Error loading file
	}

    sprite.setTexture(frontTexture);

}

void Card::draw(sf::RenderWindow& window) {
    sprite.setTexture(isShown ? frontTexture : backTexture);
    window.draw(sprite);
}

void Card::flip() {
    isShown = !isShown;
}