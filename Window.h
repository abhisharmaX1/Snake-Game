#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window {
    public:
        Window();
        Window(const std::string& title, const sf::Vector2u& size);
        ~Window();

        void beginDraw();
        void endDraw();
        void update();
        bool isDone();
        bool isFullScreen();
        
        sf::Vector2u getWindowSize();
        void toggleFlScrn();
        void draw(sf::Drawable& stuff);
        sf::RenderWindow* getRenderWindow();

    private:
        void setUp(const std::string& title, const sf::Vector2u& size);
        void create();
        void destroy();

        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        std::string m_windowTitle;
        bool m_isDone;
        bool m_isFlScrn;

};