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
    auto name1 = "(x-60)/10";
    auto name2 = "-((x-70)/10)+1";

    Function function1(name1, "x");
    Function function2(name2, "x");

    std::vector<GraphWindow::Point> points;

    std::array<double, MaxN + 1> qLast{};
    std::array<double, MaxN + 1> q{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxN + 1; ++i) {
        qLast[i] = Cx0[i];

        std::cout << " " << qLast[i];
    }

    int l2 = MaxN;

    std::array<double,  MaxN> Cm{};
    auto w = 3.1415926f / l2;

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
                    funcValue = function1.getValue(x, res);
                } else {
                    funcValue = function2.getValue(x, res);
                }

                Integral += 4.0 / 6.0 * h * (funcValue * sin(m * x * w));
            }
            for (int j = 1; j <= n - 1; j++) {
                auto x = l1 + h * j;
                if (x >= 0 && x < 60 || x >= 80) {
                    funcValue = 0;
                } else if (x <= 70) {
                    funcValue = function1.getValue(x, res);
                } else {
                    funcValue = function2.getValue(x, res);
                }

                Integral += 2.0 / 6.0 * h * (funcValue * sin(m * x * w));
            }

            std::cout << "I3 = " << Integral << std::endl;

            Cm[m] = 2.0f/MaxN * Integral;
        }
    }

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < MaxN; ++i) {
            double sum = 0;

            for (int m = 1; m < l2; ++m) {
                auto sinValue = sin(m * i * w);
                auto expValue = exp(-a * (w * w) * (float)(m * m) * MaxN * ht);

//                C = -((PI * m * sgn(i/10 - 7)*i*i - 70*PI*i*sgn(i/10-7)*i) * sin(PI * m * i) - abs(i - 70) * cos(PI * i * m))
//                /(10 * PI*PI * m*m * (i - 70)) + (7 * sgn(i/10 - 7)*sin(PI * i * m))/PI * m + (sin(PI * m * i)/(PI * m));

                sum += (Cm[m] * expValue * sinValue);
            }
            q[i] = sum;

            std::cout << " " << q[i];
        }
        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < MaxN + 1; ++i) {
        points.emplace_back(i, q[i]);
    }

    return points;
}
