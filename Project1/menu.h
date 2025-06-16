#pragma once

#include <SFML/Graphics.hpp>

class Menu {
	private:
		sf::RenderWindow& window;
		sf::Font font;
		sf::Text title;
		sf::Text classicModeText;
		sf::Text exitText;
		sf::Text timedModeText;

		sf::Text time60;
		sf::Text time90;
		sf::Text time120;
		sf::Text exitTimeMenu;

		bool timeMenu = false;

	public:
		Menu(sf::RenderWindow& window);
		int run();
};
