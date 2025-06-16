#include "menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window) {
    font.loadFromFile("Arial.TTF");

    title.setFont(font);
    title.setString("Memory Game");
    title.setCharacterSize(48);
    title.setPosition(200, 100);

    classicModeText.setFont(font);
    classicModeText.setString("1. Classic Mode");
    classicModeText.setCharacterSize(24);
    classicModeText.setPosition(250, 250);

    timedModeText.setFont(font);
    timedModeText.setString("2. Timed Mode");
    timedModeText.setCharacterSize(24);
    timedModeText.setPosition(250, 280);

    settingsText.setFont(font);
    settingsText.setString("4. Settings");
    settingsText.setCharacterSize(24);
    settingsText.setPosition(250, 310);

    exitText.setFont(font);
    exitText.setString("5. Exit Game");
    exitText.setCharacterSize(24);
    exitText.setPosition(250, 340);

    // Time SubMenu Text

    time60.setFont(font);
    time90.setFont(font);
    time120.setFont(font);
    exitTimeMenu.setFont(font);

    time60.setString("1. 60 Seconds");
    time90.setString("2. 90 Seconds");
    time120.setString("3. 120 Seconds");
    exitTimeMenu.setString("4. Return to Main Menu");

    time60.setCharacterSize(24);
    time90.setCharacterSize(24);
    time120.setCharacterSize(24);
    exitTimeMenu.setCharacterSize(24);

    time60.setPosition(250, 250);
    time90.setPosition(250, 280);
    time120.setPosition(250, 310);
    exitTimeMenu.setPosition(250, 370);

    // Settings Sub Menu
    gridSizeText.setFont(font);
    gridSizeText.setCharacterSize(24);
    gridSizeText.setPosition(250, 250);

    aiDifficultyText.setFont(font);
    aiDifficultyText.setCharacterSize(24);
    aiDifficultyText.setPosition(250, 280);

    player1NameText.setFont(font);
    player1NameText.setCharacterSize(24);
    player1NameText.setPosition(250, 310);

    player2NameText.setFont(font);
    player2NameText.setCharacterSize(24);
    player2NameText.setPosition(250, 340);

    colorSchemeText.setFont(font);
    colorSchemeText.setCharacterSize(24);
    colorSchemeText.setPosition(250, 370);

    backText.setFont(font);
    backText.setCharacterSize(24);
    backText.setPosition(250, 400);
    backText.setString("5. Back");

}

int Menu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (enteringName && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace
                    if (!nameInputBuffer.empty()) nameInputBuffer.pop_back();
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') { // Enter
                    if (settingsMenuSelect == 1) player1Name = nameInputBuffer;
                    if (settingsMenuSelect == 2) player2Name = nameInputBuffer;
                    enteringName = false;
                    settingsMenuSelect = 0;
                }
                else if (event.text.unicode < 128 && nameInputBuffer.size() < 12) {
                    nameInputBuffer += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (!timeMenu && !settingsMenu) {
                    // CLASSIC MDOE
                    if (event.key.code == sf::Keyboard::Num1) return CLASSIC_MODE;
                    // TIMED MODE
                    if (event.key.code == sf::Keyboard::Num2) timeMenu = true;
                    // SETTINGS
                    if (event.key.code == sf::Keyboard::Num4) settingsMenu = true;
                    // EXIT
                    if (event.key.code == sf::Keyboard::Num5) return EXIT;
                }
                else if (timeMenu) {
                    if (event.key.code == sf::Keyboard::Num1)
                        return TIMED60; // 60 seconds
                    if (event.key.code == sf::Keyboard::Num2)
                        return TIMED90; // 90 seconds
                    if (event.key.code == sf::Keyboard::Num3)
                        return TIMED120; // 120 seconds
                    if (event.key.code == sf::Keyboard::Num4)
                        timeMenu = false; // Go back
                }
                else if (settingsMenu) {
                    if (!enteringName && event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Num1) {
                            // Cycle grid size: 4x4, 6x6, 8x8
                            gridSize = (gridSize == 4) ? 6 : (gridSize == 6) ? 8 : 4;
                        }
                        if (event.key.code == sf::Keyboard::Num2) {
                            // Cycle AI difficulty
                            aiDifficulty = (aiDifficulty % 3) + 1;
                        }
                        if (event.key.code == sf::Keyboard::Num3) {
                            enteringName = true;
                            settingsMenuSelect = 1;
                            nameInputBuffer = player1Name;
                        }
                        if (event.key.code == sf::Keyboard::Num4) {
                            enteringName = true;
                            settingsMenuSelect = 2;
                            nameInputBuffer = player2Name;
                        }
                        //if (event.key.code == sf::Keyboard::Num5) {
                            // Cycle color scheme
                            //colorScheme = (colorScheme + 1) % 2;
                        //}
                        if (event.key.code == sf::Keyboard::Num5) {
                            settingsMenu = false;
                        }
                    }
                }
            }
        }

        window.clear();
        window.draw(title);

        if (timeMenu) {
            window.draw(time60);
            window.draw(time90);
            window.draw(time120);
            window.draw(exitTimeMenu);
        }
        else if (settingsMenu) {
            gridSizeText.setString("1. Grid Size: " + std::to_string(gridSize) + "x" + std::to_string(gridSize));
            string aiStr = (aiDifficulty == 1) ? "Easy" : (aiDifficulty == 2) ? "Medium" : "Hard";
            aiDifficultyText.setString("2. AI Difficulty: " + aiStr);
            player1NameText.setString("3. Player 1 Name: " + (enteringName && settingsMenuSelect == 1 ? nameInputBuffer + "_" : player1Name));
            player2NameText.setString("4. Player 2 Name: " + (enteringName && settingsMenuSelect == 2 ? nameInputBuffer + "_" : player2Name));
            //colorSchemeText.setString("5. Color Scheme: " + string(colorScheme == 0 ? "Default" : "Dark"));

            window.draw(gridSizeText);
            window.draw(aiDifficultyText);
            window.draw(player1NameText);
            window.draw(player2NameText);
            //window.draw(colorSchemeText);
            window.draw(backText);
        }
        else {
            window.draw(classicModeText);
            window.draw(timedModeText);
            window.draw(settingsText);
            window.draw(exitText);
        }
        window.display();
    }

    return 0;
}
