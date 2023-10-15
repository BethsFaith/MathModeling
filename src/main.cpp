#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>
#include <complex>

#include "GraphWindow.h"
#include "math/DifFunction.h"

static void pullDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}

int main() {
    Operations::Definition::init();

    int width, height;
    pullDesktopResolution(width, height);

    GraphWindow window(width, height, "Koshi", Color::WHITE, Color::GREY);

    std::vector<GraphWindow::Point> points;
    bool res;
    float iterations = 5;
    float t = 0.1;
    float x = 0;

    // точное решение
    std::cout << "Точное решение" << std::endl;

    auto name = "sqrt(3)*tg(sqrt(3)*x+pi/6)";
    Function function(name, "x");
    std::cout << name << std::endl;
    for (; x < iterations; x += t){
        auto y = function.getValue(x, res);
        if (res) {
            std::cout << "y(" << x << ") = " << y << std::endl;
            points.emplace_back(x, y);
        }
    }
    window.addFunction(points, "The exact - sqrt(3)*tg(sqrt(3)x+pi/6)", Color::PURPLE);

    points.clear();

    float point = 0.3f;
    bool pointCoincidence = false;
    auto trueValue = function.getValue(point, res);
    float curValue;

    // явная схема
    std::cout << "Явная схема" << std::endl;

    name = "Explicit scheme: y(n+1) = yn + t*(yn*yn+3)";
    std::cout << name << std::endl;

    t = 0.01;
    float y0 = 1;
    float yn = 0;
    x = 0;
    iterations = 60;
    std::cout << "y(x) = y" << std::endl;
    std::cout << "y(0) = 1" << std::endl;
    points.emplace_back(x, y0);

    for (int i{1}; i < iterations; ++i) {
        x = x+t;

        yn = y0 + t*(y0*y0+3);

        points.emplace_back(x, yn);
        std::cout << "y(" << x << ") = " << yn << std::endl;

        y0 = yn;

        if ((int)(x*100) == (int)(point*100)) {
            curValue = yn;
            pointCoincidence = true;
        }
    }
    if (pointCoincidence) {
        auto errorRate = abs(trueValue - curValue)/trueValue;
        std::cout << "Погрешность:" << errorRate << std::endl << std::endl;
    }
    window.addFunction(points, name, Color::BLUE);
    points.clear();

    // неявная схема
    std::cout << "Неявная схема" << std::endl;
    name = "Implicit scheme: yn+1 = (1 - sqrt (1 - 4*t*y0 - 12*t*t)) / (2*t)";
    std::cout << name << std::endl;

    pointCoincidence = false;
    t = 0.01;
    iterations = 55;
    y0 = 1;
    yn = 0;
    x = 0;
    std::cout << "y(x) = y" << std::endl;
    std::cout << "y(0) = 1" << std::endl;
    points.emplace_back(x, y0);

    for (int i{1}; i < iterations; ++i) {
        x = x+t;

        yn = (1 - sqrt(1-4*t*y0 - 12*t*t))/(2*t);

        points.emplace_back(x, yn);
        std::cout << "y(" << x << ") = " << yn << std::endl;

        y0 = yn;

        if ((int)(x*100) == (int)(point*100)) {
            curValue = yn;
            pointCoincidence = true;
        }
    }
    if (pointCoincidence) {
        auto errorRate = abs(trueValue - curValue)/trueValue;
        std::cout << "Погрешность:" << errorRate << std::endl << std::endl;
    }
    window.addFunction(points, name, Color::ORANGE);
    points.clear();

    // с весами
    std::cout << "C весами" << std::endl;
    name = "With scales: yn+1 = (-1 + sqrt(1 - 2ty0 - t^2*yn^2 - 6t^2))/(-t)";
    std::cout << name << std::endl;

    pointCoincidence = false;
    t = 0.01;
    iterations = 50;
    y0 = 1;
    yn = 0;
    x = 0;
    std::cout << "y(x) = y" << std::endl;
    std::cout << "y(0) = 1" << std::endl;
    points.emplace_back(x, y0);

    for (int i{1}; i < iterations; ++i) {
        x = x+t;

        yn = (-1 + sqrt(1 - 2*t*y0 - t*t*y0*y0 - 6*t*t))/(-t);

        points.emplace_back(x, yn);
        std::cout << "y(" << x << ") = " << yn << std::endl;

        if ((int)(x*100) == (int)(point*100)) {
            curValue = yn;
            pointCoincidence = true;
        }

        y0 = yn;
    }
    if (pointCoincidence) {
        auto errorRate = abs(trueValue - curValue)/trueValue;
        std::cout << "Погрешность:" << errorRate << std::endl;
    }

    window.addFunction(points, name, Color::GREEN);

    window.setXStep(0.1);
    window.setYStep(0.1);

    window.setXPrecision(1);
    window.setYPrecision(3);

    window.setXOffset(10);
    window.setYOffset(1);

    window.setView(-1, 0);

    window.start();

    return 0;
}
