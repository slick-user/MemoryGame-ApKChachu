#include "game.h"

Game::Game(sf::RenderWindow& window) : window(window) {

    // Create the main window
    cards.emplace_back("Assets/card4.png", 100.0f, 300.0f, 1);
    cards.emplace_back("Assets/card2.png", 200.0f, 300.0f, 2);
    cards.emplace_back("Assets/card3.png", 300.0f, 300.0f, 3);
    cards.emplace_back("Assets/card4.png", 100.0f, 400.0f, 1);
    cards.emplace_back("Assets/card2.png", 200.0f, 400.0f, 2);
    cards.emplace_back("Assets/card3.png", 300.0f, 400.0f, 3);

    // Create a graphical text to display
    font.loadFromFile("Arial.TTF");

    /*
    // Load a music to play
    sf::Music music;
    //if (!music.openFromFile("nice_music.ogg"))
        //return EXIT_FAILURE;

    // Play the music
    music.play();
    */

    scoreP1 = 0;
    scoreP2 = 0;
}

int Game::run() {
    // Start the game loop
    while (window.isOpen())
    {
        //          ========= INPUT LOOP =========  

        // Process events
        sf::Event event;
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Click to flip a card
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                for (auto& card:cards) {
                    if (card.isHovered(mousePos) && !card.getIsShown() && flippedCards.size() < 2 && !card.getMatched()) {
                        card.flip();
                        flippedCards.push_back(&card);

                        // Checks for pairs
                        if (flippedCards.size() == 2) {
                            if (flippedCards[0]->getID() == flippedCards[1]->getID()) {
								flippedCards[0]->setMatched(true);
                                flippedCards[1]->setMatched(true);
                                cout << "MATCH FOUND!" << endl;
                                
                                // Adding Score to relevant player
                                if (PTurn == 1) scoreP1++;
                                else if (PTurn == 2) scoreP2++;

								// Reset flipped cards
								flippedCards.clear();
							} else {
								cout << "NO MATCH!" << endl;
								// Start a timer to flip back the cards
								matchClock.restart();
								checkingForMatch = true;
							}
                        }
                        break;
                    }
                }
            }
        }

        //          ========= RENDERING =========

        // Clear screen
        window.clear();

        // Draw the sprite
        for (int i = 0; i < cards.size(); i++) {
            cards[i].draw(window);
        }

        // Update the window
        window.display();

        // ========= RESET ========
        update();

        if (gameOver) {
            sf::Text gameOverText;
            sf::Text P1;
            sf::Text P2;
            sf::Text Winner;

            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER!");
            gameOverText.setCharacterSize(48);
            gameOverText.setPosition(200, 200);

            P1.setFont(font);
            P1.setString("P1 Score : " + to_string(scoreP1));
            P1.setCharacterSize(24);
            P1.setPosition(300, 300);

            P2.setFont(font);
            P2.setString("P2 Score : " + to_string(scoreP2));
            P2.setCharacterSize(24);
            P2.setPosition(300, 330);

            Winner.setFont(font);
            Winner.setCharacterSize(24);
            Winner.setPosition(200, 370);

            if (scoreP1 > scoreP2)
                Winner.setString("Player 1 Wins!");
            else if (scoreP2 > scoreP1)
                Winner.setString("Player 2 Wins!");

            window.clear();
            for (auto& card : cards) card.draw(window);
            window.draw(gameOverText);
            window.draw(P1);
            window.draw(P2);
            window.draw(Winner);
            window.display();
            sf::sleep(sf::seconds(4));
            return 1;
        }
    }

    return 1;
}

void Game::update() {
    if (checkingForMatch && matchClock.getElapsedTime().asSeconds() > 1.0f) {
        flippedCards[0]->flip();
        flippedCards[1]->flip();
        flippedCards.clear();
        checkingForMatch = false;
        
        if (PTurn == 1) {
            PTurn = 2;
            cout << "SCORE: " << scoreP1 << endl;
        }
        else {
            PTurn = 2;
            cout << "SCORE: " << scoreP2 << endl;
        }
        
        
    } 

    // Only set gameOver to true if all cards are matched
    bool allMatched = true;
    for (auto& card : cards) {
        if (!card.getMatched()) {
            allMatched = false;
            break;
        }
    }
    if (allMatched && !gameOver) {
        gameOver = true;
    }
}