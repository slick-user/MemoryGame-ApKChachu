#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"
#include "menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Memory Game");

    int mode = 1;

    while (window.isOpen()) {
        if (mode == 1) {
            Menu menu(window);
            mode = menu.run();
        }
        else if (mode == 2) {
            Game classic(window);
            mode = classic.run();
        }

        if (mode == 0) window.close();
    }
}