#pragma once

#include <iostream>
#include "card.h"

class Game {
	private:
		std::vector<Card> cards;

		sf::RenderWindow window;

		sf::Font font;
		sf::Text text;

		bool checkingForMatch = false; // Flag to check if we are currently checking for a match
		std::vector<Card*> flippedCards;
		sf::Clock matchClock;

		int scoreP1;
		int scoreP2;

	public:
		Game();
		
		int run();
		void update();

};
