#include "Game.h"

Game::Game() : m_window("Snake Game", sf::Vector2u(800, 600)),
               snake(world.getBlockSize()), world(sf::Vector2u(800, 600)) {
    // Setting up class members
    m_clock.restart();
    srand(time(nullptr));
    m_elapsed = 0.0f;
}

Game::~Game() {

}

void Game::handleInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
		&& snake.getDirection() != Direction::Down){
		snake.setDirection(Direction::Up);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
		&& snake.getDirection() != Direction::Up){
		snake.setDirection(Direction::Down);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		&& snake.getDirection() != Direction::Right){
		snake.setDirection(Direction::Left);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		&& snake.getDirection() != Direction::Left){
		snake.setDirection(Direction::Right);
	}
}

void Game::update() {
    m_window.update();
	float timestep = 1.0f / snake.getSpeed();
	if(m_elapsed >= timestep) {
		snake.tick();
		world.update(snake);
		m_elapsed -= timestep;
        if (snake.hasLost())
            snake.reset();
	}
}


void Game::render() {
    m_window.beginDraw();
    world.render(*m_window.getRenderWindow());
	snake.render(*m_window.getRenderWindow());
    m_window.endDraw();
}

Window* Game::getWindow() {
    return &m_window;
}

sf::Time Game::getElapsed() {
    return m_clock.getElapsedTime();
}

void Game::restartClock() {
    m_elapsed += m_clock.restart().asSeconds();
}




