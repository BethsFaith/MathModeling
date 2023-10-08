//
// Created by VerOchka on 08.10.2023.
//

#include "GraphWindow.h"

GraphWindow::GraphWindow(int width, int height, const char *title, Color backgroundColor, Color cAxes)
        : Window(width, height, title, backgroundColor) {
    _axisColor = getColor(cAxes);
    _xOffset = 0;
    _yOffset = 0;
    _scale = defaultSegSize;
    _axesStep = 1;
    _axesPrecision = 0;
    _curMark = 0;
}

void GraphWindow::start() {
    Window::start();
}

void GraphWindow::update(double deltaTime) {
    Window::update(deltaTime);

    static const double zoomKeysSens = 1 / 2e5;
    static const double zoomWheelSens = zoomKeysSens * 3;
    static const double moveSens = 1 / 1e3;

    static const int max_scale = sqrt(defaultSegSize);
    static const int min_scale = 1;

    if (input.isKeyboardKeyPressed(sf::Keyboard::Up) || input.mouseWheelDelta == 1) {
        if (input.isKeyboardKeyPressed(sf::Keyboard::Up))
            _scale += _scale * deltaTime * zoomKeysSens;
        if (input.mouseWheelDelta == 1)
            _scale += _scale * deltaTime * zoomWheelSens;
        _scale = std::min(_scale, (double) max_scale);
        while (defaultSegSize / _axesStep < _scale) {
            _axesStep /= 2;
            if (_axesStep < 1)
                _axesPrecision++;
        }
    }
    if (input.isKeyboardKeyPressed(sf::Keyboard::Down) || input.mouseWheelDelta == -1) {
        if (input.isKeyboardKeyPressed(sf::Keyboard::Down))
            _scale -= _scale * deltaTime * zoomKeysSens;
        if (input.mouseWheelDelta == -1)
            _scale -= _scale * deltaTime * zoomWheelSens;
        _scale = std::max(_scale, (double) min_scale);
        while (_scale * 2 <= defaultSegSize / _axesStep) {
            if (_axesStep < 1)
                _axesPrecision--;
            _axesStep *= 2;
        }
    }

    if (input.isKeyboardKeyPressed(sf::Keyboard::W))
        _yOffset += deltaTime / _scale * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::A))
        _xOffset -= deltaTime / _scale * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::S))
        _yOffset -= deltaTime / _scale * moveSens;
    if (input.isKeyboardKeyPressed(sf::Keyboard::D))
        _xOffset += deltaTime / _scale * moveSens;
    dragging();

    if (input.isKeyboardKeyDown(sf::Keyboard::Num1)) {
        _curMark--;
        if (_curMark == -1) {
            _curMark = _funcs.size() - 1;
        }
    }
    if (input.isKeyboardKeyDown(sf::Keyboard::Num2)) {
        _curMark++;
        if (_curMark == _funcs.size())
            _curMark = 0;
    }
}

void GraphWindow::display() {
    window.clear(cBackground);

    drawAxes();

    for (auto &func: _funcs)
        construct(func.first, func.second);

    graphMark();

    window.display();
}

void GraphWindow::addFunction(Function &func, Color color) {
    _funcs.emplace_back(func, getColor(color));
}

void GraphWindow::setView(double _xOffset, double _yOffset) {
    _xOffset = _xOffset;
    _yOffset = _yOffset;
}

void GraphWindow::dragging() {
    static int prevX;
    static int prevY;
    if (input.isMouseButtonPressed(sf::Mouse::Left)) {
        int deltaX = input.mouseX - prevX;
        int deltaY = input.mouseY - prevY;
        _xOffset -= deltaX / _scale;
        _yOffset += deltaY / _scale;
    }
    prevX = input.mouseX;
    prevY = input.mouseY;
}

bool GraphWindow::onScreen(int cX, int cY) const {
    return 0 <= cX && cX < sWidth && 0 <= cY && cY < sHeight;
}

double GraphWindow::toMathX(int x) const {
    return (x - sWidth / 2) / _scale + _xOffset;
}

double GraphWindow::toMathY(int y) const {
    return -(y - sHeight / 2) / _scale + _yOffset;
}

int GraphWindow::toCrdX(double x) const {
    return (x - _xOffset) * _scale + sWidth / 2;
}

int GraphWindow::toCrdY(double y) const {
    return -(y - _yOffset) * _scale + sHeight / 2;
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
        markupText.setFillColor(_axisColor);
        INIT = 1;
    }

    int x0 = toCrdX(0);
    x0 = std::max(x0, markupLength);
    x0 = std::min(x0, sWidth - 1 - markupLength);
    Utilities::line(window, x0, 0, x0, sHeight - 1, _axisColor);
    double stY = Utilities::getCloseLowerNum(toMathY(sHeight - 1), _axesStep);
    for (double curY = stY; curY <= toMathY(0); curY += _axesStep) {
        if (curY) {
            Utilities::line(window, x0 - markupLength, toCrdY(curY), x0 + markupLength, toCrdY(curY), _axisColor);
            markupText.setString(Utilities::dtos(curY, _axesPrecision));
            int textX = x0 - 2 * markupLength - markupText.getLocalBounds().left - markupText.getLocalBounds().width;
            if (x0 < sWidth / 5)
                textX = x0 + 2 * markupLength - markupText.getLocalBounds().left + 1;
            int textY = toCrdY(curY) - markupText.getLocalBounds().top - markupText.getLocalBounds().height / 2;
            markupText.setPosition(textX, textY);
            window.draw(markupText);
        }
    }
    int y0 = toCrdY(0);
    y0 = std::max(y0, markupLength);
    y0 = std::min(y0, sHeight - 1 - markupLength);
    Utilities::line(window, 0, y0, sWidth - 1, y0, _axisColor);
    double stX = Utilities::getCloseLowerNum(toMathX(0), _axesStep);
    for (double curX = stX; curX < toMathX(sWidth - 1); curX += _axesStep) {
        if (curX) {
            Utilities::line(window, toCrdX(curX), y0 - markupLength, toCrdX(curX), y0 + markupLength, _axisColor);
            markupText.setString(Utilities::dtos(curX, _axesPrecision));
            int textX = toCrdX(curX) - markupText.getLocalBounds().left - markupText.getLocalBounds().width / 2;
            int textY = y0 + 2 * markupLength - markupText.getLocalBounds().top + 1;
            if (y0 > sHeight * 4 / 5)
                textY = y0 - 2 * markupLength - markupText.getLocalBounds().top - markupText.getLocalBounds().height;
            markupText.setPosition(textX, textY);
            window.draw(markupText);
        }
    }
}

void GraphWindow::construct(Function &func, sf::Color color) {
    bool isArgX = func.getArgument() == "x";
    for (int cArg = 0; cArg < (isArgX ? sWidth : sHeight); cArg++) {
        double mArg1 = isArgX ? toMathX(cArg) : toMathY(cArg);
        bool isSuccess;
        double mRes1 = func.getValue(mArg1, isSuccess);

        if (!isSuccess || isnan(mRes1))
            continue;

        double mArg2 = isArgX ? toMathX(cArg + 1) : toMathY(cArg + 1);
        double mRes2 = func.getValue(mArg2, isSuccess);

        if (!isSuccess || isnan(mRes2))
            continue;

        int cRes1 = isArgX ? toCrdY(mRes1) : toCrdX(mRes1);
        int cRes2 = isArgX ? toCrdY(mRes2) : toCrdX(mRes2);

        if (!onScreen(isArgX ? cArg : cRes1, isArgX ? cRes1 : cArg) &&
            !onScreen(isArgX ? cArg : cRes2, isArgX ? cRes2 : cArg))
            continue;

        if (cRes2 < cRes1)
            std::swap(cRes1, cRes2);

        cRes1 = std::max(cRes1, 0);
        cRes2 = std::min(cRes2, isArgX ? sHeight - 1 : sWidth - 1);
        Utilities::line(window, isArgX ? cArg : cRes1, isArgX ? cRes1 : cArg, isArgX ? cArg : cRes2,
                        isArgX ? cRes2 : cArg, color);
    }
}

void GraphWindow::graphMark() {
    static const int markPrecision = 6;
    static const int dotRadius = 5;
    static std::vector<sf::CircleShape> dots;
    static bool INIT = 0;

    if (!INIT) {
        dots.resize(_funcs.size());
        for (int i = 0; i < _funcs.size(); i++) {
            dots[i].setFillColor(_funcs[i].second);
            dots[i].setRadius(dotRadius);
        }
        INIT = 1;
    }

    if (!Utilities::isCursorInWindow(window)) {
        window.setTitle(std::string("Graph_XY"));
        return;
    }

    if (_funcs.empty())
        return;

    bool isArgX = _funcs[_curMark].first.getArgument() == "x";
    int cArg = isArgX ? input.mouseX : input.mouseY;
    double mArg = isArgX ? toMathX(cArg) : toMathY(cArg);

    bool isSuccessful;
    double mRes = _funcs[_curMark].first.getValue(mArg, isSuccessful);;

    if (!isSuccessful)
        mRes = NAN;

    std::string strX = Utilities::dtos(isArgX ? mArg : mRes, markPrecision);
    std::string strY = Utilities::dtos(isArgX ? mRes : mArg, markPrecision);

    window.setTitle(std::string("Graph_XY |") + std::string(" ID: ") + std::to_string(_curMark + 1) +
                    std::string(" X: ") + strX + std::string(" Y: ") + strY);

    if (isnan(mRes))
        return;

    int cDotX = isArgX ? cArg : toCrdX(mRes);
    int cDotY = isArgX ? toCrdY(mRes) : cArg;
    bool isOnScreen = 0 <= cDotX + dotRadius && cDotX - dotRadius < sWidth && 0 <= cDotY + dotRadius &&
                      cDotY - dotRadius < sHeight;

    if (isOnScreen) {
        dots[_curMark].setPosition(cDotX - dotRadius, cDotY - dotRadius);
        window.draw(dots[_curMark]);
    }
}
