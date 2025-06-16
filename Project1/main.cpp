#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"
#include "menu.h"
#include "timedMode.h"

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
        else if (mode == 31) {
            TimedMode timed(window, 60);
            mode = timed.run();
        }
        else if (mode == 32) {
            TimedMode timed(window, 90);
            mode = timed.run();
        }
        else if (mode == 33) {
            TimedMode timed(window, 120);
            mode = timed.run();
        }
        else if (mode == 4) {
            // Implementation of AI Mode
        }

        if (mode == 0) window.close();
    }
}