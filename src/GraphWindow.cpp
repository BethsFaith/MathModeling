//
// Created by VerOchka on 08.10.2023.
//

#include "GraphWindow.h"

GraphWindow::GraphWindow(int width, int height, const char *title, Color backgroundColor, Color cAxes)
        : Window(width, height, title, backgroundColor) {
    _axisColor = getColor(cAxes);
    _xOffset = 0;
    _yOffset = 0;
    _scaleX = defaultSegSize;
    _scaleY = defaultSegSize;
    _axesStep = 1;

    _curFunctionIndex = -1;
}

void GraphWindow::start() {
    Window::start();
}

void GraphWindow::update(double deltaTime) {
    Window::update(deltaTime);

    if (input.isKeyboardKeyPressed(sf::Keyboard::Left)){
        if (_curFunctionIndex > 0) {
            --_curFunctionIndex;
        }
    }
    if (input.isKeyboardKeyPressed(sf::Keyboard::Right)){
        if (_curFunctionIndex < _functions.size()-1) {
            ++_curFunctionIndex;
        }
    }

    static const double zoomKeysSens = 1 / 2e5;
    static const double zoomWheelSens = zoomKeysSens * 3;

    if (input.mouseWheelDelta == 1) {
        _scaleX += _scaleX * deltaTime * zoomWheelSens;
        _scaleY += _scaleY * deltaTime * zoomWheelSens;
        _scaleX = std::min(_scaleX, (double)maxSegSize);
        _scaleY = std::min(_scaleY, (double)maxSegSize);
    }
    if (input.mouseWheelDelta == -1) {
        _scaleX -= _scaleX * deltaTime * zoomWheelSens;
        _scaleY -= _scaleY * deltaTime * zoomWheelSens;
        _scaleX = std::max(_scaleX, (double)minSegSize);
        _scaleY = std::max(_scaleY, (double)minSegSize);
    }

    static const double moveSens = 1 / 1e3;

    if (input.isKeyboardKeyPressed(sf::Keyboard::W))
        _yOffset += deltaTime / _scaleY * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::A))
        _xOffset -= deltaTime / _scaleX * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::S))
        _yOffset -= deltaTime / _scaleY * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::D))
        _xOffset += deltaTime / _scaleX * moveSens;
    dragging();
}

void GraphWindow::dragging() {
    static int prevX;
    static int prevY;
    if (input.isMouseButtonPressed(sf::Mouse::Left)) {
        int deltaX = input.mouseX - prevX;
        int deltaY = input.mouseY - prevY;
        _xOffset -= deltaX / _scaleX;
        _yOffset += deltaY / _scaleY;
    }
    prevX = input.mouseX;
    prevY = input.mouseY;
}

void GraphWindow::display() {
    window.clear(cBackground);

    drawAxes();

    construct(_functions.at(_curFunctionIndex));

    window.display();
}

void GraphWindow::addFunction(const std::vector<Point> &points, const std::string &name, Color color) {
    if (_curFunctionIndex == -1) {
        _curFunctionIndex = 0;
    }
    _functions.push_back({.points = points, .color = getColor(color), .name = name});
}

void GraphWindow::drawAxes() {
    static const int markupLength = 6;
    static sf::Font markupFont;
    static sf::Text markupText;
    static bool INIT = 0;
    if (!INIT) {
        markupFont.loadFromFile("D:\\CPlusPlus\\Projects\\Labs\\Math\\Lab1_Koshi\\rsrc\\fonts\\calibri.ttf");
        markupText.setFont(markupFont);
        markupText.setCharacterSize(15);
        markupText.setFillColor(sf::Color::Black);
        INIT = 1;
    }

    auto function = _functions[_curFunctionIndex];

    auto minX = std::min_element(function.points.begin(), function.points.end(),
                                 [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    })->x;
    auto maxX = std::max_element(function.points.begin(), function.points.end(),
                                 [](const Point& p1, const Point& p2) {
                                     return p1.x < p2.x;
                                 })->x;

    int countMarks = std::abs((int)(minX - maxX)) + 2;
//    _scaleX = width / countMarks / 2;
//    if (_scaleX > defaultSegSize) {
//        _scaleX = defaultSegSize;
//    } else if (_scaleX < minSegSize) {
//        _scaleX = minSegSize;
//    }
    if (countMarks > _axesStep) {
        countMarks /= _axesStep;
    }

    for (int i = minX; i < maxX + 1; i += _axesStep) {
        Utilities::drawLine(window, toCrdX(i), toCrdY(0),
                            toCrdX(i + _axesStep), toCrdY(0), _axisColor);
        markupText.setString(std::to_string(i));
        markupText.setPosition(toCrdX(i), toCrdY(0));
        window.draw(markupText);
    }

    auto minY = std::min_element(function.points.begin(), function.points.end(),
                                 [](const Point& p1, const Point& p2) {
                                     return p1.y < p2.y;
                                 })->y;
    auto maxY = std::max_element(function.points.begin(), function.points.end(),
                                 [](const Point& p1, const Point& p2) {
                                     return p1.y < p2.y;
                                 })->y;
    countMarks = (std::abs((int)maxY - (int)minY) + 2);
//    _scaleY = height / countMarks / 2;
//    if (_scaleY > defaultSegSize) {
//        _scaleY = defaultSegSize;
//    } else if (_scaleY < minSegSize) {
//        _scaleY = minSegSize;
//    }
    if (countMarks > _axesStep) {
        countMarks /= _axesStep;
    }

    for (int i = (int)minY-1; i < maxY + 1;i += _axesStep) {
        Utilities::drawLine(window, toCrdX(0), toCrdY(i),
                            toCrdX(0), toCrdY(i+ _axesStep), _axisColor);
        markupText.setString(std::to_string(i));
        markupText.setPosition(toCrdX(0), toCrdY((i)));
        window.draw(markupText);
    }
}

void GraphWindow::construct(DrawableFunction &function) {
    auto &points = function.points;
    for (int i{}; i < points.size()-1; ++i) {
        Utilities::drawLine(window, toCrdX(points.at(i).x), toCrdY(points.at(i).y),
                            toCrdX(points.at(i+1).x),  toCrdY(points.at(i+1).y), function.color);
    }
}


void GraphWindow::setView(double xOffset, double yOffset) {
    _xOffset = xOffset;
    _yOffset = yOffset;
}

bool GraphWindow::onScreen(int cX, int cY) const {
    return 0 <= cX && cX < width && 0 <= cY && cY < height;
}

int GraphWindow::toCrdX(double x) const {
    auto res =  (x - _xOffset) * _scaleX + width / 2;
    return res;
}

int GraphWindow::toCrdY(double y) const {
    auto res =  -(y - _yOffset) * _scaleY + height / 2;
    return res;
}

void GraphWindow::setAxesStep(double axesStep) {
    _axesStep = axesStep;
}
