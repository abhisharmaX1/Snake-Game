#include "World.h"

World::World(sf::Vector2u windowSize) {
    this->blockSize = 16;

    this->windowSize = windowSize;
    respawnApple();
    this->item.setFillColor(sf::Color::Red);
    this->item.setRadius(blockSize / 2);

    //creating boundary
    for (int i = 0; i < 4; i++) {
        this->bounds[i].setFillColor(sf::Color(150, 0, 0));
        
        if (i % 2 == 1)
            this->bounds[i].setSize(sf::Vector2f(this->windowSize.x, this->blockSize));
        else
            this->bounds[i].setSize(sf::Vector2f(this->blockSize, this->windowSize.y)); 

        if (i < 2) {
            this->bounds[i].setPosition(0, 0);
        }
        else {
            this->bounds[i].setOrigin(this->bounds[i].getSize());
            this->bounds[i].setPosition(sf::Vector2f(this->windowSize));
        }

    }
}

World::~World() {

}

int World::getBlockSize() {
    return this->blockSize;
}

void World::respawnApple() {
    int maxX = (this->windowSize.x / this->blockSize) - 2;
    int maxY = (this->windowSize.y / this->blockSize) - 2;
    this->itemPos = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
    this->item.setPosition(this->itemPos.x * this->blockSize, this->itemPos.y * this->blockSize);
}

void World::update(Snake& snake) {
    if (snake.getPosition() == itemPos) {
        snake.extend();
        snake.increaseScore();
        respawnApple();
    }

    int gridSizeX = this->windowSize.x / this->blockSize;
    int gridSizeY = this->windowSize.y / this->blockSize;

    if (snake.getPosition().x <= 0 || snake.getPosition().x >= gridSizeX ||
        snake.getPosition().y <= 0 || snake.getPosition().y >= gridSizeY) {
            snake.lose();
        }
}

void World::render(sf::RenderWindow& window) {
    for (int i = 0; i < 4; i++) {
        window.draw(bounds[i]);
    }
    window.draw(item);
}