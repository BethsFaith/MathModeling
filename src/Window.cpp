//
// Created by VerOchka on 30.09.2023.
//

#include "Window.h"

Window::Window(int width_, int height_, const char *title, Color backgroundColor)
        : window(sf::VideoMode(width_, height_), title), width(width_), height(height_) {
    cBackground = getColor(backgroundColor);
}

void Window::start() {
    while (window.isOpen()) {
        // Обрабатываем очередь событий в цикле
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                input.keyboardKeyPressed(event.key.code);
            if (event.type == sf::Event::KeyReleased)
                input.keyboardKeyReleased(event.key.code);
            if (event.type == sf::Event::MouseMoved) {
                input.isMouseMoved = 1;
                input.mouseX = event.mouseMove.x;
                input.mouseY = event.mouseMove.y;
            }
            if (event.type == sf::Event::MouseEntered)
                input.isMouseEntered = 1;
            if (event.type == sf::Event::MouseLeft)
                input.isMouseLeft = 1;
            if (event.type == sf::Event::MouseButtonPressed)
                input.mouseButtonPressed(event.mouseButton.button);
            if (event.type == sf::Event::MouseButtonReleased)
                input.mouseButtonReleased(event.mouseButton.button);
            if (event.type == sf::Event::MouseWheelScrolled) {
                input.isMouseWheelScrolled = 1;
                input.mouseWheelDelta = event.mouseWheelScroll.delta;
            }
        }
        double deltaTime = (double) clock.restart().asMicroseconds();
        update(deltaTime);
        input.refresh();
        display();
    }
}

void Window::update(double deltaTime) {
}

void Window::display() {
    window.clear(cBackground);
    window.display();
}

sf::Color Window::getColor(Color color) {
    switch (color) {
        case RED:
            return sf::Color::Red;
        case WHITE:
            return sf::Color::White;
        case BLUE:
            return sf::Color::Blue;
        case YELLOW:
            return sf::Color::Yellow;
        case ORANGE:
            return {255, 135, 23};
        case GREEN:
            return {68, 148, 74};
        case GREY:
            return {133, 130, 127};
        case BLACK:
            return sf::Color::Black;
        case PURPLE:
            return {192,5,248};
        case PINK:
            return {255, 20, 147};
    }
}
