//
// Created by VerOchka on 30.09.2023.
//

#ifndef LAB1_KOSHI_WINDOW_H
#define LAB1_KOSHI_WINDOW_H

#include "Color.h"
#include "InputSystem.h"

class Window {
public:
    Window(int width_, int height_, const char* title, Color backgroundColor);
    virtual ~Window() = default;

    virtual void start();

protected:
    static sf::Color getColor(Color color);

    virtual void update(double deltaTime);
    virtual void display();

    sf::RenderWindow window;
    InputSystem input;

    int width;
    int height;

    sf::Clock clock;
    sf::Color cBackground;
};


#endif //LAB1_KOSHI_WINDOW_H
