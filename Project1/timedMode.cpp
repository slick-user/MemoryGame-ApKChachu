#include "timedMode.h"

TimedMode::TimedMode(sf::RenderWindow& window, int seconds) : window(window), timeLimit(seconds) {

    srand(static_cast<unsigned>(time(0))); // Seed the RNG

    int ids[16];
    int index = 0;

    // Create pairs of 1 to 8 (each twice)
    for (int i = 1; i <= 8; ++i) {
        ids[index++] = i;
        ids[index++] = i;
    }

    for (int i = 15; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(ids[i], ids[j]);
    }

    for (int i = 0; i < 16; ++i) {
        int row = i / 4;
        int col = i % 4;

        float x = 100.0f + col * 100.0f;
        float y = 200.0f + row * 100.0f;

        int id = ids[i];

        string texturePath = "Assets/card" + std::to_string(id) + ".png";
        cards.emplace_back(texturePath.c_str(), x, y, id);
    }

    // Create a graphical text to display
    font.loadFromFile("Arial.TTF");

    score = 0;
}

int TimedMode::run() {
    // Start the game loop
    gameClock.restart(); // Start the timer
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
                for (auto& card : cards) {
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
                                score++;

                                // Reset flipped cards
                                flippedCards.clear();
                            }
                            else {
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

        timerText.setFont(font);
        int timeRemaining = timeLimit - int(gameClock.getElapsedTime().asSeconds());
        timerText.setString("Time Remaining: " + to_string(timeRemaining));
        timerText.setCharacterSize(24);
        timerText.setPosition(10, 10);
        window.draw(timerText);

        // Update the window
        window.display();

        // ========= RESET ========
        update();
        
        // set gameOver to true if all cards are matched or time has ended
        if (gameClock.getElapsedTime().asSeconds() >= timeLimit) {
            gameOver = true;
        }

        // GAME OVER STATE
        if (gameOver) {
            sf::Text gameOverText;
            sf::Text P;
            sf::Text Winner;

            gameOverText.setFont(font);
            gameOverText.setString("GAME OVER!");
            gameOverText.setCharacterSize(48);
            gameOverText.setPosition(200, 200);

            P.setFont(font);
            P.setString("Score : " + to_string(score));
            P.setCharacterSize(24);
            P.setPosition(300, 300);
            
            Winner.setFont(font);
            Winner.setCharacterSize(24);
            Winner.setPosition(200, 370);

            window.clear();
            for (auto& card : cards) card.draw(window);
            window.draw(gameOverText);
            window.draw(P);
            window.display();
            sf::sleep(sf::seconds(4));
            return 1;
        }
    }

    return 1;
}

void TimedMode::update() {
    if (checkingForMatch && matchClock.getElapsedTime().asSeconds() > 1.0f) {
        flippedCards[0]->flip();
        flippedCards[1]->flip();
        flippedCards.clear();
        checkingForMatch = false;

    }

    bool allMatched = true;
    for (auto& card : cards) {
        if (!card.getMatched()) {
            allMatched = false;
            break;
        }
    }

    // BONUS SCORE and Game Over Condition
    if (allMatched && !gameOver) {
        int timeRemaining = timeLimit - int(gameClock.getElapsedTime().asSeconds());
        if (timeRemaining > 0) {
            score += timeRemaining;
        }

        gameOver = true;
    }
}