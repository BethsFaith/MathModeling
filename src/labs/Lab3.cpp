//
// Created by VerOchka on 11.11.2023.
//

#include "Lab3.h"

void Lab3::work(int width, int height) {
    GraphWindow window(1440, 720, "Koshi", Color::WHITE, Color::GREY);

    std::vector<GraphWindow::Point> points;

    auto name1 = "(x-60)/10"; // z = y0, v = x0
    auto name2 = "-((x-70)/10)+1";

    Function function(name1, "x");
    Function function2(name2, "x");

    for (int i = 60; i < 71; ++i) {
        bool res;
        auto y = function.getValue(i, res);
        if (res) {
            points.emplace_back(i, y);
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    for (int i = 70; i < 81; ++i) {
        bool res;
        auto y = function2.getValue(i, res);
        if (res) {
            points.emplace_back(i, y);
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    window.addFunction(points, "y1 = (x-60)/10; \ny2 = -(x-70)/10", Color::RED);

    // подготовка
    std::array<float, 100> Cx{};
    for (int i{}; i < 60; ++i) {
        Cx[i] = 0;
    }
    for (int i{60}; i < 70; ++i) {
        bool res;
        auto y = function.getValue(i, res);
        if (res) {
            Cx[i] = y;
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    for (int i{70}; i < 81; ++i) {
        bool res;
        auto y = function2.getValue(i, res);
        if (res) {
            Cx[i] = y;
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    for (int i{81}; i < MaxX; ++i) {
        Cx[i] = 0;
    }

    points.clear();
    std::cout << "\n\nЯвная схема" << std::endl;

    points = explicitScheme(Cx);
    window.addFunction(points, "Explicit", Color::BLUE);

    points.clear();
    std::cout << "\n\nНеявная схема" << std::endl;

    points = implicitScheme(Cx);
    window.addFunction(points, "Implicit", Color::GREEN);

    window.setXStep(20);
    window.setYStep(0.25);

    window.setXPrecision(0);
    window.setYPrecision(2);

    window.setXOffset(250);
    window.setYOffset(0);
    window.start();
}

std::vector<GraphWindow::Point> Lab3::explicitScheme(std::array<float, MaxX> Cx0) {
    std::vector<GraphWindow::Point> points;

    float a  = (u * t)/h;

    std::array<float, MaxX> CLastN = Cx0;
    std::array<float, MaxX> CN{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxX; ++i) {
        std::cout << " " << CLastN[i];
    }

    float tn = 0;
    for (int n = 1; n < MaxN; ++n) {
        CN[0] = Cx0[0];
        CN[MaxX-1] = Cx0[MaxX-1];

        tn += h*t;

        std::cout << std::endl << "n" << n << ": ";
        std::cout << " " << CN[0];
        for (int i{1}; i < MaxX-1; ++i) {
            CN[i] = CLastN[i] + a * h * tn * ((CLastN[i+1] - 2 * CLastN[i] + CLastN[i-1]) / (h*h));
            std::cout << " " << CN[i];
        }
        std::cout << " " << CN[MaxX-1];
        CLastN = CN;
    }
    for (int i{}; i < MaxX; ++i) {
        points.emplace_back(i, CN[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab3::implicitScheme(std::array<float, MaxX> Cx0) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxX> alpha{};
    std::array<float, MaxX> beta{};
    std::array<float, MaxX> CLastN = Cx0;
    std::array<float, MaxX> CN{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxX; ++i) {
        std::cout << " " << CLastN[i];
    }

    float ai, bi, ci, fi;
    for (int time = 0; time < 100; time += (t*100)) {
        CN[0] = Cx0[0];
        CN[MaxX-1] = Cx0[MaxX-1];

        std::cout << std::endl << "n" << time << ": ";
        for (int i{1}; i < MaxX-1; ++i) {
            ai = k / (h * h);
            bi = 2 * ai + 1 / t;
            ci = ai;
            fi = -1 * CLastN[i] / t;

            alpha[i] = ai / (bi - ci * alpha[i-1]);
            beta[i] = (ci * beta[i - 1] - fi)/(bi - ci * alpha[i-1]);

            CN[i] = alpha[i]*CLastN[i+1]+beta[i];
            std::cout << " " << CN[i];
        }
        std::cout << " " << CN[MaxX-1];
    }
    for (int i{}; i < MaxX; ++i) {
        points.emplace_back(i, CN[i]);
    }

    return points;
}
