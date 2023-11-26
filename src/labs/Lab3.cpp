//
// Created by VerOchka on 11.11.2023.
//

#include "Lab3.h"

void Lab3::work(int width, int height) {
    GraphWindow window(width, height, "Koshi", Color::WHITE, Color::GREY);

    std::vector<GraphWindow::Point> points;

    auto name1 = "0.0001*x*x+1";
    Function function(name1, "x");

    for (int i = 0; i < N; ++i) {
        bool res;
        auto y = function.getValue(i, res);
        if (res) {
            points.emplace_back(i, y);
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    window.addFunction(points, name1, Color::RED);

    // подготовка
    std::array<float, N + 1> Cx{};
    for (int i{0}; i < N+1; ++i) {
        bool res;
        auto y = function.getValue(i, res);
        if (res) {
            Cx[i] = y;
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
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

    points = analyticScheme(function, function);
    window.addFunction(points, "Analytic", Color::PURPLE);

    window.setXStep(20);
    window.setYStep(0.25);

    window.setXPrecision(0);
    window.setYPrecision(2);

    window.setXOffset(250);
    window.setYOffset(0);
    window.start();
}

std::vector<GraphWindow::Point> Lab3::explicitScheme(std::array<float, N + 1> Cx0) {
    std::vector<GraphWindow::Point> points;

    std::array<float, N + 1> uLastByT = Cx0;
    std::array<float, N + 1> u{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < N + 1; ++i) {
        std::cout << " " << uLastByT[i];
    }

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < N; ++i) {
            u[i] = uLastByT[i] + (k*k * ht) * (uLastByT[i + 1] - 2 * uLastByT[i] + uLastByT[i - 1]) / (hx * hx);

            std::cout << " " << u[i];
        }
        uLastByT = u;
        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < N + 1; ++i) {
        points.emplace_back(i, u[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab3::implicitScheme(std::array<float, N + 1> Cx0) {
    std::vector<GraphWindow::Point> points;

    std::array<float, N + 1> f = Cx0;
    std::array<float, N + 1> u{};

    std::array<float, N + 1> p{};
    std::array<float, N + 1> q{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < N + 1; ++i) {
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
        for (int i = 1; i < N - 1; ++i) {
            auto phi = bi + ai * p[i - 1];
            p[i] = -ci / phi;
            q[i] = (f[i] - ai * q[i-1]) / phi;
        }
        p[N - 1] = (f[N - 1] - ai * q[N - 2]) / (bi + ai * p[N - 2]);

        u[N - 1] = q[N - 1];

        for (int i = N - 2; i >= 0; --i) {
            u[i] = f[i + 1] * p[i] + q[i];

            std::cout << " " << u[i];
        }

        f = u;

        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < N + 1; ++i) {
        points.emplace_back(i, u[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab3::analyticScheme(Function &f1, Function &f2) {
    std::vector<GraphWindow::Point> points;

    std::array<double, N + 1> u{};

    std::cout << std::endl << "n0 : ";

    int l2 = N;

    std::array<double,  N> Cm{};
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
                funcValue = f1.getValue(x, res);

                Integral += 4.0 / 6.0 * h * (funcValue * sin(m * x * w));
            }
            for (int j = 1; j <= n - 1; j++) {
                auto x = l1 + h * j;
                funcValue = f1.getValue(x, res);

                Integral += 2.0 / 6.0 * h * (funcValue * sin(m * x * w));
            }

            std::cout << "I3 = " << Integral << std::endl;

            Cm[m] = 2.0f/(float)l2 * Integral;
        }
    }

    double t = 0;
    do {
        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < N; ++i) {
            double sum = 0;

            for (int m = 1; m < l2; ++m) {
                auto sinValue = sin((float)m * (float)i * w);
                auto expValue = exp(-(k*k) * (w * w) * (float)(m * m) * t);

                sum += (Cm[m] * expValue * sinValue);
            }
            u[i] = sum;

            std::cout << " " << u[i];
        }
        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < N + 1; ++i) {
        points.emplace_back(i, u[i]);
    }

    return points;
}
