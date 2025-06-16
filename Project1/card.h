#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Card {
	protected:
		sf::Texture frontTexture;
		sf::Texture backTexture;

		sf::Sprite sprite;

		int id = 0; // Unique identifier for the card
		bool isShown = false;
		bool matched = false;

		void loadTexture(const char* path);

	public:
		Card(const char* path = "Assets/card1.png", float x = 100.0f, float y = 300.0f, int id = 0);

		// SETTERS
		void setPosition(float x, float y);
		void setMatched(bool i) { matched = i; }

		// GETTERS
		int getMatched() const { return matched;  }
		int getID() const { return id; }
		bool getIsShown() const { return isShown; }
		sf::Sprite& getSprite() { return sprite; }

		void draw(sf::RenderWindow& window);

		bool isHovered(const sf::Vector2f& mousePos) const;
		void flip();
};
