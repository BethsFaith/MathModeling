//
// Created by VerOchka on 08.10.2023.
//

#include "GraphWindow.h"

GraphWindow::GraphWindow(int width, int height, const char *title, Color backgroundColor, Color cAxes)
        : Window(width, height, title, backgroundColor) {
    _axisColor = getColor(cAxes);
    _xOffset = 0;
    _yOffset = 0;
    _xScale = defaultSegSize;
    _yScale = defaultSegSize;
    _xStep = 1;
    _yStep = 1;

    _curFunctionIndex = -1;
}

void GraphWindow::start() {
    Window::start();
}

void GraphWindow::update(double deltaTime) {
    Window::update(deltaTime);

    _lastDeltaTime = deltaTime;

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
        _xScale += _xScale * deltaTime * zoomWheelSens;
        _yScale += _yScale * deltaTime * zoomWheelSens;
        _xScale = std::min(_xScale, (double)maxSegSize);
        _yScale = std::min(_yScale, (double)maxSegSize);

//        if (_yStep < 1000) {
//            _yStep += _yStep * 0.1;
//        }
//        if (_xStep  < 1000) {
//            _xStep += _xStep * 0.1;
//        }
//        if (_xPrecision < 5) {
//            ++_xPrecision;
//        }
//        if (_yPrecision < 5) {
//            ++_yPrecision;
//        }
    }
    if (input.mouseWheelDelta == -1) {
        _xScale -= _xScale * deltaTime * zoomWheelSens;
        _yScale -= _yScale * deltaTime * zoomWheelSens;
        _xScale = std::max(_xScale, (double)minSegSize);
        _yScale = std::max(_yScale, (double)minSegSize);


//        if (_yStep > 0.02) {
//            _yStep -= _yStep * 0.1;
//        }
//        if (_xStep > 0.02) {
//            _xStep -= _xStep * 0.1;
//        }
//        if (_xPrecision > 2) {
//            --_xPrecision;
//        }
//        if (_yPrecision > 2) {
//            --_yPrecision;
//        }
    }

    static const double moveSens = 1 / 1e3;

    if (input.isKeyboardKeyPressed(sf::Keyboard::W))
        _yOffset += deltaTime / _yScale * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::A))
        _xOffset -= deltaTime / _xScale * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::S))
        _yOffset -= deltaTime / _yScale * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::D))
        _xOffset += deltaTime / _xScale * moveSens;
    dragging();
}

void GraphWindow::dragging() {
    static int prevX;
    static int prevY;
    if (input.isMouseButtonPressed(sf::Mouse::Left)) {
        int deltaX = input.mouseX - prevX;
        int deltaY = input.mouseY - prevY;
        _xOffset -= deltaX / _xScale;
        _yOffset += deltaY / _yScale;
    }
    prevX = input.mouseX;
    prevY = input.mouseY;
}

void GraphWindow::display() {
    window.clear(cBackground);

    drawAxes();

    for (auto func : _functions){
        construct(func);
    }

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
        markupFont.loadFromFile("..\\..\\rsrc\\fonts\\calibri.ttf");
        markupText.setFont(markupFont);
        markupText.setCharacterSize(15);
        markupText.setFillColor(sf::Color::Black);
        INIT = 1;
    }

    auto function = _functions[_curFunctionIndex];

    window.setTitle(function.name);

    auto minX = std::min_element(function.points.begin(), function.points.end(),
                                 [](const Point& p1, const Point& p2) {
        return p1.x < p2.x;
    })->x;
    auto maxX = std::max_element(function.points.begin(), function.points.end(),
                                 [](const Point& p1, const Point& p2) {
                                     return p1.x < p2.x;
                                 })->x;
    for (int i = 1; i < _functions.size(); ++i) {
        auto min = std::min_element(_functions[i].points.begin(), _functions[i].points.end(),
                                    [](const Point& p1, const Point& p2) {
                                        return p1.x < p2.x;
                                    })->x;
        auto max = std::max_element(_functions[i].points.begin(), _functions[i].points.end(),
                                    [](const Point& p1, const Point& p2) {
                                        return p1.x < p2.x;
                                    })->x;
        if (minX > min) {
            minX = min;
        }
        if (maxX < max) {
            maxX = max;
        }
    }

    minX = std::min(0.0f, minX);

    auto iterations = (maxX - minX)/_xStep + 2;
    for (float i = 0; i < iterations; ++i) {
        Utilities::drawLine(window, toCrdX(minX + i*_xStep), toCrdY(0),
                            toCrdX(minX + (i+1)*_xStep), toCrdY(0), _axisColor, 2);
        markupText.setString(Utilities::dtos(minX + i*_xStep, _xPrecision));
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
    for (int i = 1; i < _functions.size(); ++i) {
        auto min = std::min_element(_functions[i].points.begin(), _functions[i].points.end(),
                                  [](const Point& p1, const Point& p2) {
                                      return p1.y < p2.y;
                                  })->y;
        auto max = std::max_element(_functions[i].points.begin(), _functions[i].points.end(),
                                    [](const Point& p1, const Point& p2) {
                                        return p1.y < p2.y;
                                    })->y;
        if (minY > min) {
            minY = min;
        }
        if (maxY < max) {
            maxY = max;
        }
    }

    minY = std::min(0.0f, std::abs(minY));

    iterations = (maxY - minY)/_yStep + 1;
    for (float i = 0; i < iterations; ++i) {
        Utilities::drawLine(window, toCrdX(0), toCrdY(minY + i * _xStep),
                            toCrdX(0), toCrdY(minY + (i+1) * _xStep), _axisColor, 2);
        markupText.setString(Utilities::dtos(minY + i*_yStep, _yPrecision));;
        markupText.setPosition(toCrdX(0), toCrdY((i)));
        window.draw(markupText);
    }

    for (int i{}; i < _functions.size(); ++i){
        auto crdX1 = width*0.9;
        auto crdX2 =width*0.95;
        auto crdY =  height*0.1 + height*0.05*i;

        Utilities::drawLine(window, crdX1, crdY,
                            crdX2, crdY, _functions.at(i).color, 2);
        markupText.setString(_functions.at(i).name);
        markupText.setPosition(crdX1, crdY);
        window.draw(markupText);
    }
}

void GraphWindow::construct(DrawableFunction &function) {
    auto &points = function.points;
    for (int i{}; i < points.size()-1; ++i) {
        Utilities::drawLine(window, toCrdX(points.at(i).x / _xStep), toCrdY(points.at(i).y / _yStep),
                            toCrdX(points.at(i + 1).x / _xStep), toCrdY(points.at(i + 1).y / _yStep), function.color,
                            3);
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
    auto res = (x - _xOffset) * _xScale + width / 2;
    return res;
}

int GraphWindow::toCrdY(double y) const {
    auto res = -(y - _yOffset) * _yScale + height / 2;
    return res;
}

void GraphWindow::setXPrecision(int xPrecision) {
    _xPrecision = xPrecision;
}

void GraphWindow::setYPrecision(int yPrecision) {
    _yPrecision = yPrecision;
}

void GraphWindow::setXStep(double xStep) {
//    static const double zoomKeysSens = 1 / 2e5;
//    static const double zoomWheelSens = zoomKeysSens * 3;
//    for (int i = 0; i < _xStep - xStep; ++i) {
//        _xScale -= _xScale * _lastDeltaTime * zoomWheelSens;
//        _yScale -= _yScale * _lastDeltaTime * zoomWheelSens;
//        _xScale = std::max(_xScale, (double)minSegSize);
//        _yScale = std::max(_yScale, (double)minSegSize);
//    }
//    for (int i = 0; i < xStep - _xStep; ++i) {
//        _xScale += _xScale * _lastDeltaTime * zoomWheelSens;
//        _yScale += _yScale * _lastDeltaTime * zoomWheelSens;
//        _xScale = std::min(_xScale, (double)maxSegSize);
//        _yScale = std::min(_yScale, (double)maxSegSize);
//    }
    _xStep = xStep;
}

void GraphWindow::setYStep(double yStep) {
    _yStep = yStep;
}

void GraphWindow::setXOffset(double xOffset) {
    _xOffset *= xOffset;
}

void GraphWindow::setYOffset(double yOffset) {
    _yOffset *= yOffset;
}

void GraphWindow::setYScale(double yScale) {
    _yScale = yScale;
}

void GraphWindow::setXScale(double xScale) {
    _xScale = xScale;
}

void GraphWindow::clean() {
    _functions.clear();
}
