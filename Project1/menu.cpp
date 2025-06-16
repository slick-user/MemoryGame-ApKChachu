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

    exitText.setFont(font);
    exitText.setString("2. Exit Game");
    exitText.setCharacterSize(24);
    exitText.setPosition(250, 280);

}

int Menu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) return 2;
                if (event.key.code == sf::Keyboard::Num2) return 0;
            }
        }

        window.clear();
        window.draw(title);
        window.draw(classicModeText);
        window.draw(exitText);
        window.display();
    }
    return 0;
}
