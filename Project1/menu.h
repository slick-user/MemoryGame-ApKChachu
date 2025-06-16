#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

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

		sf::Text settingsText;

		string player1Name = "Player 1";
		string player2Name = "Player 2";
		int gridSize = 4; // Default 4x4
		int aiDifficulty = 1; // 1: Easy, 2: Medium, 3: Hard
		int colorScheme = 0; // 0: Default, 1: Dark, 2: Neon

		sf::Text gridSizeText;
		sf::Text aiDifficultyText;
		sf::Text player1NameText;
		sf::Text player2NameText;
		sf::Text colorSchemeText;
		sf::Text backText;

		int settingsMenuSelect = 0;
		string nameInputBuffer;
		bool enteringName = false;

		bool timeMenu = false;
		bool settingsMenu = false;

		enum MenuResult {
			EXIT = 0,
			MENU = 1,
			CLASSIC_MODE = 2,
			TIMED60 = 31,
			TIMED90 = 32,
			TIMED120 = 33,
		};

	public:
		Menu(sf::RenderWindow& window);
		int run();
};
