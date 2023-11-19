//
// Created by VerOchka on 11.11.2023.
//

#include "Lab3.h"

void Lab3::work(int width, int height) {
    GraphWindow window(width, height, "Koshi", Color::WHITE, Color::GREY);

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
    std::array<float, MaxN + 1> Cx{};
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
    for (int i{81}; i < MaxN + 1; ++i) {
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

    std::cout << "\n\nАналитическая" << std::endl;

    points = analyticScheme(Cx);
    window.addFunction(points, "Analytic", Color::PURPLE);

    window.setXStep(20);
    window.setYStep(0.25);

    window.setXPrecision(0);
    window.setYPrecision(2);

    window.setXOffset(250);
    window.setYOffset(0);
    window.start();
}

std::vector<GraphWindow::Point> Lab3::explicitScheme(std::array<float, MaxN + 1> Cx0) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxN + 1> qLast = Cx0;
    std::array<float, MaxN + 1> q{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxN + 1; ++i) {
        std::cout << " " << qLast[i];
    }

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < MaxN; ++i) {
            q[i] = qLast[i] + (a * ht) * (qLast[i + 1] - 2 * qLast[i] + qLast[i - 1] / (hx * hx));

            std::cout << " " << q[i];
        }
        qLast = q;
        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < MaxN + 1; ++i) {
        points.emplace_back(i, q[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab3::implicitScheme(std::array<float, MaxN + 1> Cx0) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxN + 1> qLast = Cx0;
    std::array<float, MaxN + 1> q{};

    std::array<float, MaxN + 1> alpha{};
    std::array<float, MaxN + 1> beta{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxN + 1; ++i) {
        alpha[i] = 0;
        beta[i] = 0;

        std::cout << " " << qLast[i];
    }

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < MaxN; ++i) {
            float ai = ht / (hx * hx);
            float bi = 2 * ai + 1 / ht;
            float ci = ai;
            float fi = -1 * qLast[i] / ht;

            alpha[i] = ai / (bi - ci * alpha[i - 1]);
            beta[i] = (ci * beta[i - 1] - fi) / (bi - ci * alpha[i - 1]);
        }
        for (int i = MaxN - 1; i >= 0; --i) {
            q[i] = qLast[i + 1] * alpha[i] + beta[i];

            std::cout << " " << q[i];
        }

        qLast = q;
        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < MaxN + 1; ++i) {
        points.emplace_back(i, q[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab3::analyticScheme(std::array<float, MaxN + 1> Cx0) {
    std::vector<GraphWindow::Point> points;
//    auto w = 3.1415926f / MaxN;

    std::array<double, MaxN + 1> qLast{};
    std::array<double, MaxN + 1> q{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxN + 1; ++i) {
        qLast[i] = Cx0[i];

        std::cout << " " << qLast[i];
    }

//    int l = MaxN;
    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < MaxN; ++i) {
            double C;
            double sum = 0;

            int l;
            if (i <= 70) {
                l = 70;
            } else {
                l = 80;
            }

            auto w = 3.1415926f / MaxN;

            for (int m = 1; m < MaxN-1; ++m) {
                auto sinValue = sin(m * i * w);
                auto expValue = exp(-a * (w * w) * (float)(m * m) * t);

                if (i <= 70) {
                    C = ((float)2 / MaxN) * (sin(l * m * w) / (10 * m * m * w * w) - (cos(l * m * w)) / (m * w) -
                            sin(60 * m * w) / (10 * m * m * w * w));
                } else {
                    C = ((float)2 / MaxN) * (-sin(l * m * w) / (10 * m * m * w * w) + sin(70 * m * w) / (10 * m * m * w * w) +
                            cos(70 * m * w) / (m * w));
                }
                sum += (C * expValue * sinValue);
            }
            q[i] = sum;

            std::cout << " " << q[i];
        }
        t = t + ht;
    } while (t < 100 + ht / 2);

    for (int i{}; i < MaxN + 1; ++i) {
        points.emplace_back(i, q[i]);
    }

    return points;
}