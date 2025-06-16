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

    exitText.setFont(font);
    exitText.setString("3. Exit Game");
    exitText.setCharacterSize(24);
    exitText.setPosition(250, 320);

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

}

int Menu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (!timeMenu) {
                    // CLASSIC MDOE
                    if (event.key.code == sf::Keyboard::Num1) return 2;
                    // TIMED MODE
                    if (event.key.code == sf::Keyboard::Num2) {
                        timeMenu = true;
                    }
                    if (event.key.code == sf::Keyboard::Num3) return 0;
                }
                else {
                    if (event.key.code == sf::Keyboard::Num1)
                        return 31; // 60 seconds
                    if (event.key.code == sf::Keyboard::Num2)
                        return 32; // 90 seconds
                    if (event.key.code == sf::Keyboard::Num3)
                        return 33; // 120 seconds
                    if (event.key.code == sf::Keyboard::Num4)
                        timeMenu = false; // Go back
                }
            }
        }

        window.clear();
        window.draw(title);

        if (!timeMenu) {
            window.draw(classicModeText);
            window.draw(timedModeText);
            window.draw(exitText);
        }
        else {
            window.draw(time60);
            window.draw(time90);
            window.draw(time120);
            window.draw(exitTimeMenu);
        }

        window.display();
    }

    return 0;
}
