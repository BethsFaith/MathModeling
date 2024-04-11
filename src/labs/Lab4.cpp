//
// Created by VerOchka on 10.12.2023.
//

#include "Lab4.h"

void Lab4::work(int width, int height) {
    GraphWindow window(width, height, "Koshi", Color::WHITE, Color::GREY);

    std::vector<GraphWindow::Point> points;
    std::vector<GraphWindow::Point> points2;

    Function function1("-(x/10-2)*(x/10-2)+1", "x");

    auto name2 = "sin(x)+100";
    Function function2(name2, "x");

    for (int i = 10; i < 31; ++i) {
        bool res;
        auto y = function1.getValue(i, res);
        if (res) {
            points.emplace_back(i, y);
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    window.addFunction(points, "-(x/10-2)^2+1", Color::RED);

    float y = 0;
    while(y <= 10) {
        bool res;
        auto x = function2.getValue(y, res);
        if (res) {
            points2.emplace_back(x, y);
        } else {
            std::cout << "Не получилось получить значение на точке с y = " << y;
        }
        y += 0.001;
    }
//    window.addFunction(points2, name2, Color::PURPLE);

    std::array<float, N + 1> q{};
    for (int i = 0; i < 10; ++i) {
        q[i] = 0;
    }
    for (int i = 10; i < 31; ++i) {
        bool res;
        auto y = function1.getValue(i, res);
        if (res) {
            q[i] = y;
        } else {
            std::cout << "Не получилось получить значение на точке с x = " << i;
        }
    }
    for (int i = 31; i < 100; ++i) {
        q[i] = 0;
    }

    auto points3 = convectionDiffusion(q);
    window.addFunction(points3, "convdif", Color::GREEN);

    window.setXStep(10);
    window.setYStep(0.25);

    window.setXPrecision(0);
    window.setYPrecision(2);

    window.setXOffset(250);
    window.setYOffset(0);

    window.start();
}

std::vector<GraphWindow::Point> Lab4::convectionDiffusion(std::array<float, N + 1> q) {
    std::vector<GraphWindow::Point> points;

    float l1 = 1.0f;
    float l2 = 0.0f;
    float u = 0.7f;

    float sigma = 0.5f;

    std::array<float, N + 1> zn{};
    std::array<float, N + 1> A{};
    std::array<float, N + 1> B{};
    std::array<float, N + 1> C{};
    std::array<float, N + 1> F{};
    std::array<float, N + 1> p1{};
    std::array<float, N + 1> p2{};

    int mu = 1;
    A[0] = 0;
    B[0] = (-u / (2 * hx) + mu / (hx * hx)) * sigma;
    C[0] = 1.0 / (2 * ht) + B[0] + mu * l1 * sigma / hx;

    for (int i = 1; i < N; i++) {
        A[i] = (u / (2 * hx) + mu / (hx * hx)) * sigma;
        B[i] = (-u / (2 * hx) + mu / (hx * hx)) * sigma;
        C[i] = 1 / ht + A[i] + B[i];
    }
   /* for (int i = 0; i < N; i++) {
        zn[i] = C[i] - p1[i] * A[i];
        p1[i + 1] = B[i] / zn[i];
    }*/

    double t = 0;
    do {
        double l3 = sin(t);

        F[0] = q[0] * (1 / (2 * ht) - (-u / (2 * hx) + mu / (hx * hx) + mu * l1 / hx) * (1 - sigma)) +
               q[1] * (-u / (2 * hx) + mu / (hx * hx)) * (1 - sigma) - mu * l2 / hx;

        std::cout << std::endl << "t" << t << ": ";

        for (int i = 1; i < N; ++i) {
            F[i]= q[i] * (1 / ht - 2 * (1 - sigma) * mu / (hx * hx))
                  + q[i + 1] * (-u / (2 * hx) + mu / (hx * hx)) * (1 - sigma)
                  + q[i - 1] * (u / (2 * hx) + mu / (hx * hx)) * (1 - sigma);
        }
        for (int i = 0; i < N; i++) {
            zn[i] = C[i] - p1[i] * A[i];
            p1[i + 1] = B[i] / zn[i];
            p2[i + 1] = (F[i] + A[i] * p2[i]) / zn[i];
        }

        q[N] = l3;
        for (int i = N - 1; i >= 0; i--){
            q[i] = p1[i + 1] * q[i + 1] + p2[i + 1];

            std::cout << " " << q[i];
        }

        t = t + ht;
    } while (t < T + ht / 2);

    for (int i{}; i < N+1; ++i) {
        points.emplace_back(i, q[i]);
    }

    return points;
}