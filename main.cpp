#include "Game.h"

int main() {
    Game game;
    while (!game.getWindow()->isDone()) {
        // game loop
        game.handleInput();
        game.update();
        game.render();
        // sf::sleep(sf::seconds(0.2)); // Sleep for 0.2 seconds.
        game.restartClock();
    }
}