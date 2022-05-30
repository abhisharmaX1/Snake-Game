#include "Window.h"

Window::Window() {
    Window::setUp("Window", {640, 480});
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
    Window::setUp(title, size);
}

Window::~Window() {
    Window::destroy();
}

void Window::beginDraw() {
    m_window.clear(sf::Color::Black);
}

void Window::endDraw() {
    m_window.display();
}

void Window::update() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_isDone = true;
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
            Window::toggleFlScrn();
    }    
}

bool Window::isDone() {
    return m_isDone;
}

bool Window::isFullScreen() {
    return m_isFlScrn;
}



sf::Vector2u Window::getWindowSize() {
    return m_windowSize;
}

void Window::toggleFlScrn() {
    m_isFlScrn = !m_isFlScrn;
    m_window.close();
    Window::create();
}

// void Window::draw(sf::Drawable& stuff) {
//     m_window.draw(stuff);
// }

void Window::setUp(const std::string& title, const sf::Vector2u& size) {
    m_windowTitle = title;
    m_windowSize = size;
    m_isDone = false;
    m_isFlScrn = false;
    //m_window.setFramerateLimit(60);
    Window::create();
}

void Window::create() {
    auto style = (m_isFlScrn ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style); 
}



void Window::destroy() {
    m_window.close();
}

sf::RenderWindow* Window::getRenderWindow(){ 
    return &m_window; 
}