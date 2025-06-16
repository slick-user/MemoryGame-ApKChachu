#include "game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Memory Game") {

    // Create the main windo

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
                                std::cout << "MATCH FOUND!" << std::endl;
								// Reset flipped cards
								flippedCards.clear();
							} else {
								std::cout << "NO MATCH!" << std::endl;
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
            if (!cards[i].getMatched()) 
                cards[i].draw(window);
        }

        // Update the window
        window.display();

        // ========= RESET ========
        update();
    }

    return EXIT_SUCCESS;
}

void Game::update() {
    if (checkingForMatch && matchClock.getElapsedTime().asSeconds() > 1.0f) {
        flippedCards[0]->flip();
        flippedCards[1]->flip();
        flippedCards.clear();
        checkingForMatch = false;
    }
}