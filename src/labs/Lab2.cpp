//
// Created by VerOchka on 27.10.2023.
//

#include "Lab2.h"

void Lab2::work(int width, int height) {
    GraphWindow window(width, height, "Koshi", Color::WHITE, Color::GREY);

    std::vector<GraphWindow::Point> points;

    float y0 = 0, t = 0.1f, u = 0.1f;
    int r = 10, x0 = 80, h = 1;
    float a  = (u * t)/(float)h;

    int iterations = 100;

    auto name = "z+sqrt(r*r-(x-v)*(x-v))"; // z = y0, v = x0
    Function function(name, "x");

    function.setVariable("z", y0);
    function.setVariable("v", x0);
    function.setVariable("r", r);
    for (int i = 0; i < 70; ++i) {
        points.emplace_back(i, 0);
    }
    for (int i = 70; i < 91; ++i) {
        bool res;
        auto y = function.getValue(i, res);
        if (res) {
            points.emplace_back(i, y);
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    for (int i = 91; i < 100; ++i) {
        points.emplace_back(i, 0);
    }
    window.addFunction(points, "y0 + sqrt (r^2 - (x-x0)^2) ", Color::RED);

    window.setXStep(20);
    window.setYStep(1);

    window.setXPrecision(0);
    window.setYPrecision(0);

    window.setXOffset(250);
    window.setYOffset(0);

    window.start();

    std::cout << "Правый уголок" << std::endl;


}
