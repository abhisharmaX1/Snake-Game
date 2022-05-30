#include "Snake.h"

Snake::Snake(int blockSize) {
    this->size = blockSize;
    Snake::bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
    Snake::reset();
}

Snake::~Snake() {

}

Direction Snake::getDirection() {
    return this->dir;
}

int Snake::getSpeed() {
    return this->speed;
}

int Snake::getLives() {
    return this->lives;
}

int Snake::getScore() {
    return this->score;
}

sf::Vector2i Snake::getPosition() {
    return (!this->snakeBody.empty() ? this->snakeBody.front().position : sf::Vector2i(1,1));
}

void Snake::setDirection(Direction dir) {
    this->dir = dir;
}

void Snake::increaseScore() {
    score += 10;
}

bool Snake::hasLost() {
    return this->status;
}

void Snake::lose() {
    this->status = true;
}

void Snake::toggleLost() {
    this->status = !status;
}

void Snake::extend() {
    if (this->snakeBody.empty()) return;
    snakeSegment& tail = this->snakeBody[this->snakeBody.size() - 1];

    if (this->snakeBody.size() > 1) {
        snakeSegment& nextToTail = this->snakeBody[this->snakeBody.size() - 2];
        if (tail.position.x == nextToTail.position.x) {
            if (tail.position.y > nextToTail.position.y) {
                this->snakeBody.push_back(snakeSegment(tail.position.x,
                                                       nextToTail.position.y + 1));
            } else {
                this->snakeBody.push_back(snakeSegment(tail.position.x,
                                                       nextToTail.position.y - 1));
            }
        } else if (tail.position.y == nextToTail.position.y) {
            if (tail.position.x > nextToTail.position.x) {
                this->snakeBody.push_back(snakeSegment(tail.position.x + 1,
                                                       nextToTail.position.y));
            } else {
                this->snakeBody.push_back(snakeSegment(tail.position.x - 1,
                                                       nextToTail.position.y));
            }
        }
    } else {
        if (this->dir == Direction::Up) {
            this->snakeBody.push_back(snakeSegment(tail.position.x, tail.position.y + 1));
        } else if (this->dir == Direction::Down) {
            this->snakeBody.push_back(snakeSegment(tail.position.x, tail.position.y - 1));
        } else if (this->dir == Direction::Left) {
            this->snakeBody.push_back(snakeSegment(tail.position.x + 1, tail.position.y));
        } else if (this->dir == Direction::Right) {
            this->snakeBody.push_back(snakeSegment(tail.position.x - 1, tail.position.y));
        }
    }
}

void Snake::reset() {
    this->snakeBody.clear();
    this->snakeBody.push_back(snakeSegment(5, 7));
    this->snakeBody.push_back(snakeSegment(5, 6));
    this->snakeBody.push_back(snakeSegment(5, 5));

    Snake::setDirection(Direction::None);
    this->speed = 15;
    this->lives = 3;
    this->score = 0;
    this->status = false;
}

void Snake::move() {
    for (int i = this->snakeBody.size() - 1; i > 0; i--) {
        this->snakeBody[i].position = this->snakeBody[i - 1].position;
    }
    if (this->dir == Direction::Up) {
        this->snakeBody[0].position.y--;
    } else if (this->dir == Direction::Left) {
        this->snakeBody[0].position.x--;
    } else if (this->dir == Direction::Right) {
        this->snakeBody[0].position.x++;
    } else if (this->dir == Direction::Down) {
        this->snakeBody[0].position.y++;
    }
}

// another term for update
void Snake::tick() {
    if (this->snakeBody.empty()) return;
    if (this->dir == Direction::None) return;
    move();
    checkCollision();
}

void Snake::cut(int segments) {
    for (int i = 0; i < segments; i++) {
        this->snakeBody.pop_back();
    }
    lives--;
    if (lives <= 0) {
        lose();
        return;
    }
}

void Snake::render(sf::RenderWindow& window) {
    if (this->snakeBody.empty()) return;

    auto head = this->snakeBody.begin();
    this->bodyRect.setFillColor(sf::Color::Yellow);
    this->bodyRect.setPosition(head->position.x * this->size,
                               head->position.y * this->size);
    window.draw(this->bodyRect);

    this->bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = this->snakeBody.begin() + 1; itr != this->snakeBody.end(); ++itr) {
        this->bodyRect.setPosition(itr->position.x * this->size, itr->position.y * this->size);
        window.draw(this->bodyRect);
    }
}

void Snake::checkCollision() {
    if (this->snakeBody.size() < 5) return;
    snakeSegment& head = this->snakeBody.front();
    for (auto itr = this->snakeBody.begin() + 1; itr != this->snakeBody.end(); ++itr) {
        if (itr->position == head.position) {
            int segments = this->snakeBody.end() - itr;
            cut(segments);
            break;
        }
    }
}

