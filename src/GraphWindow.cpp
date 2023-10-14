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
    _axesStep = 1;

    _curFunctionIndex = -1;
}

void GraphWindow::start() {
    Window::start();
}

void GraphWindow::update(double deltaTime) {
    Window::update(deltaTime);

    if (input.isKeyboardKeyPressed(sf::Keyboard::A)){
        if (_curFunctionIndex > 0) {
            --_curFunctionIndex;
        }
    }
    if (input.isKeyboardKeyPressed(sf::Keyboard::D)){
        if (_curFunctionIndex < _functions.size()-1) {
            ++_curFunctionIndex;
        }
    }
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
    _scaleX = width / countMarks / 2;

    for (int i = minX; i < maxX + 1; i += _axesStep) {
        Utilities::drawLine(window, toCrdX(i * _axesStep), toCrdY(0),
                            toCrdX((i+1)  * _axesStep), toCrdY(0), _axisColor);
        markupText.setString(std::to_string(i));
        markupText.setPosition(toCrdX((i)  * _axesStep), toCrdY(0));
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
    countMarks = std::abs((int)(maxY - minY)) + 2;
    _scaleY = width / countMarks / 2;

    for (int i = minY-1; i < maxY + 1; i += _axesStep) {
        Utilities::drawLine(window, toCrdX(0), toCrdY(i * _axesStep),
                            toCrdX(0), toCrdY((i+1)  * _axesStep), _axisColor);
        markupText.setString(std::to_string(i));
        markupText.setPosition(toCrdX(0), toCrdY((i)  * _axesStep));
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


void GraphWindow::setView(double _xOffset, double _yOffset) {
    _xOffset = _xOffset;
    _yOffset = _yOffset;
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
