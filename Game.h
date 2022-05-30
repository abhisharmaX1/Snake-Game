#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"

class Game {
    public:
        Game();
        ~Game();

        void handleInput();
        void update();
        void render();
        Window* getWindow();

        void restartClock();
        sf::Time getElapsed();
    private:
        Window m_window;

        sf::Clock m_clock;
        float m_elapsed;
        
        World world;
        Snake snake;

};