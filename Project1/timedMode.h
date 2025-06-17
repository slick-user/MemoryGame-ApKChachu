#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>

#include "card.h"

using namespace std;

class TimedMode {

	private:
		sf::RenderWindow& window;

		sf::Font font;
		sf::Text timerText;

		vector<Card> cards;

		bool checkingForMatch = false; // Flag to check if we are currently checking for a match
		vector<Card*> flippedCards;
		sf::Clock matchClock;

		int score;

		int timeLimit;
		sf::Clock gameClock;

		bool gameOver = false;

	public:
		TimedMode(sf::RenderWindow& window, int seconds);

		int run();
		void update();

};
