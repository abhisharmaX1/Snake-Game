#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct snakeSegment {
    snakeSegment(int x, int y) : position(x, y) {

    }
    sf::Vector2i position;
};

using snakeContainer = std::vector<snakeSegment>;

enum class Direction {None, Up, Down, Left, Right};

class Snake {
    public:
        Snake(int blockSize);
        ~Snake();

        Direction getDirection();
        int getSpeed();
        int getLives();
        int getScore();
        sf::Vector2i getPosition();

        void setDirection(Direction dir);
        
        void increaseScore();
        bool hasLost();

        void lose();
        void toggleLost();
        void extend();
        void reset();
        void move();
        void tick();
        void cut(int segments);
        void render(sf::RenderWindow& window);

    private:
       void checkCollision();

       snakeContainer snakeBody;
       Direction dir;
       int size;
       int speed;
       int lives;
       int score;
       bool status;
       sf::RectangleShape bodyRect; 
};