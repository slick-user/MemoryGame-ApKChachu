#pragma once

#include <SFML/Graphics.hpp>

class Menu {
	private:
		sf::RenderWindow& window;
		sf::Font font;
		sf::Text title;
		sf::Text classicModeText;
		sf::Text exitText;

	public:
		Menu(sf::RenderWindow& window);
		int run();
};
