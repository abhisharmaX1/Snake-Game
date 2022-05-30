#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class World {
    public:
        World(sf::Vector2u windowSize);
        ~World();

        int getBlockSize();
        void respawnApple();

        void update(Snake& snake);
        void render(sf::RenderWindow& window);

    private:
        sf::Vector2u windowSize;
        sf::Vector2i itemPos;
        int blockSize;

        sf::CircleShape item;
        sf::RectangleShape bounds[4];
};