#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include "card.h"


using namespace std;

class Game {
	private:
		sf::RenderWindow& window;

		sf::Font font;

		vector<Card> cards;

		bool checkingForMatch = false; // Flag to check if we are currently checking for a match
		vector<Card*> flippedCards;
		sf::Clock matchClock;

		int scoreP1;
		int scoreP2;

		int PTurn; // If 1 then it is P1 Turn Else on 2 P2 Turn

		bool gameOver = false;

	public:
		Game(sf::RenderWindow& window);
		
		int run();
		void update();

};
