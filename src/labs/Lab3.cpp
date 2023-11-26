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

    points = analyticScheme(function, function2);
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

    std::array<float, MaxN + 1> uLastByT = Cx0;
    std::array<float, MaxN + 1> u{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxN + 1; ++i) {
        std::cout << " " << uLastByT[i];
    }

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < MaxN; ++i) {
            u[i] = uLastByT[i] + (k*k * ht) * (uLastByT[i + 1] - 2 * uLastByT[i] + uLastByT[i - 1]) / (hx * hx);

            std::cout << " " << u[i];
        }
        uLastByT = u;
        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < MaxN + 1; ++i) {
        points.emplace_back(i, u[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab3::implicitScheme(std::array<float, MaxN + 1> Cx0) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxN + 1> f = Cx0;
    std::array<float, MaxN + 1> u{};

    std::array<float, MaxN + 1> p{};
    std::array<float, MaxN + 1> q{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxN + 1; ++i) {
        p[i] = 0;
        q[i] = 0;

        std::cout << " " << f[i];
    }

    float sigma = (k * k * ht) / (hx * hx);
    float ai = -sigma;
    float bi = 2 * sigma + 1;
    float ci = -sigma;

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        p[0] = - ci/bi;
        q[0] = f[0] / bi;
        for (int i = 1; i < MaxN-1; ++i) {
            auto phi = bi + ai * p[i - 1];
            p[i] = -ci / phi;
            q[i] = (f[i] - ai * q[i-1]) / phi;
        }
        p[MaxN-1] = (f[MaxN-1] - ai*q[MaxN-2])/(bi + ai * p[MaxN-2]);

        u[MaxN-1] = q[MaxN-1];

        for (int i = MaxN - 2; i >= 0; --i) {
            u[i] = f[i + 1] * p[i] + q[i];

            std::cout << " " << u[i];
        }

        f = u;

        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < MaxN + 1; ++i) {
        points.emplace_back(i, u[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab3::analyticScheme(Function &f1, Function &f2) {
    std::vector<GraphWindow::Point> points;

    std::array<double, MaxN + 1> u{};

    std::cout << std::endl << "n0 : ";

    int l2 = MaxN;

    std::array<double,  MaxN> Cm{};
    auto w = 3.1415926f / (float)l2;

    {
        double Integral; // здесь будет интеграл
        double h = hx;// задаём шаг интегрирования
        double l1 = 0.0f;

        double n = (l2 - l1) / h; // задаём число разбиений n
        for (int m = 1; m < l2; ++m) {
            bool res;
            Integral = 0;

            double funcValue;
            for (int j = 1; j <= n; j++) {
                auto x = l1 + h * (j - 0.5);
                if (x < 60 || x >= 80) {
                    funcValue = 0;
                } else if (x <= 70) {
                    funcValue = f1.getValue(x, res);
                } else {
                    funcValue = f2.getValue(x, res);
                }

                Integral += 4.0 / 6.0 * h * (funcValue * sin(m * x * w));
            }
            for (int j = 1; j <= n - 1; j++) {
                auto x = l1 + h * j;
                if (x >= 0 && x < 60 || x >= 80) {
                    funcValue = 0;
                } else if (x <= 70) {
                    funcValue = f1.getValue(x, res);
                } else {
                    funcValue = f2.getValue(x, res);
                }

                Integral += 2.0 / 6.0 * h * (funcValue * sin(m * x * w));
            }

            std::cout << "I3 = " << Integral << std::endl;

            Cm[m] = 2.0f/(float)l2 * Integral;
        }
    }

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < MaxN; ++i) {
            double sum = 0;

            for (int m = 1; m < l2; ++m) {
                auto sinValue = sin((float)m * (float)i * w);
                auto expValue = exp(-k * (w * w) * (float)(m * m) * t);

                sum += (Cm[m] * expValue * sinValue);
            }
            u[i] = sum;

            std::cout << " " << u[i];
        }
        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < MaxN + 1; ++i) {
        points.emplace_back(i, u[i]*1.015f);
    }

    return points;
}
