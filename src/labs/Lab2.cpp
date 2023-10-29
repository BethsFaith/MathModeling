//
// Created by VerOchka on 27.10.2023.
//

#include "Lab2.h"

void Lab2::work(int width, int height) {
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
    window.addFunction(points, "y = (x-60)/10; y = -(x-70)/10", Color::RED);

    window.setXStep(20);
    window.setYStep(1);

    window.setXPrecision(0);
    window.setYPrecision(0);

    window.setXOffset(250);
    window.setYOffset(0);

    float t = 0.1f, u = 0.6f, h = 1;
    float a  = (u * t)/h;

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
    std::cout << "Правый уголок" << std::endl;

    points = right(Cx, a);
    window.addFunction(points, "Right", Color::BLUE);

    points = center(Cx, a);
    window.addFunction(points, "Center", Color::PURPLE);

    points = cabaret(Cx, a);
    window.addFunction(points, "Cabaret", Color::GREEN);

    points = lincomb(Cx, a);
    window.addFunction(points, "linkomb", Color::ORANGE);

    window.start();
}

std::vector<GraphWindow::Point> Lab2::left(std::array<float, MaxX> Cx, float a) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxN> CLastI{};
    std::array<float, MaxN> Ci{};

    std::cout << std::endl << "i" << 0 << ": ";
    for (int n{0}; n < MaxN; ++n) {
        CLastI[n] = 0;
        std::cout << " " << CLastI[n];
    }

    std::cout << "Левый уголок" << std::endl;
    for (int i = 1; i < MaxX; ++i) {
        std::cout << std::endl << "i" << i << ": ";
        Ci[0] = Cx[i];
        std::cout << " " << Ci[0];
        for (int n = 0; n < MaxN - 1; ++n) {
            auto y = (CLastI[n] + Ci[n]) / 2;
            Ci[n + 1] = y;
            std::cout << " " << Ci[n + 1];
        }
        points.emplace_back(i, MaxN-1);
        CLastI = Ci;
    }
    std::sort(points.begin(), points.end(), [](GraphWindow::Point A, GraphWindow::Point B){
        return A.x < B.x;
    });
    return points;
}

std::vector<GraphWindow::Point> Lab2::right(std::array<float, MaxX> Cx, float a) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxN> CNextI{};
    std::array<float, MaxN> Ci{};

    std::cout << std::endl << "i" << 0 << ": ";
    for (int n{0}; n < MaxN; ++n) {
        CNextI[n] = 0;
        std::cout << " " << CNextI[n];
    }
    for (int i = MaxX - 1; i >= 0; --i) {
        std::cout << std::endl << "i" << i << ": ";
        Ci[0] = Cx[i];
        std::cout << " " << Ci[0];
        for (int n = 0; n < MaxN-1; ++n) {
            auto y =  Ci[n] + a*(CNextI[n] - Ci[n]);
            Ci[n + 1] = y;
            std::cout << " " << Ci[n + 1];
        }
        points.emplace_back(i, Ci[MaxN-1]);
        CNextI = Ci;
    }

    std::sort(points.begin(), points.end(), [](GraphWindow::Point A, GraphWindow::Point B){
        return A.x < B.x;
    });

    return points;
}

std::vector<GraphWindow::Point> Lab2::center(std::array<float, MaxX> Cx0, float a) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxX> CLastN = Cx0;
    std::array<float, MaxX> CN{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxX; ++i) {
        std::cout << " " << CLastN[i];
    }

    for (int n = 1; n < MaxN; ++n) {
        CN[0] = Cx0[0];
        CN[MaxX-1] = Cx0[MaxX-1];

        std::cout << std::endl << "n" << n << ": ";
        std::cout << " " << CN[0];
        for (int i{1}; i < MaxX-1; ++i) {
            CN[i] = CLastN[i] + a * ((CLastN[i+1] - CLastN[i-1]) / 2);
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

std::vector<GraphWindow::Point> Lab2::cabaret(std::array<float, MaxX> Cx0, float a) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxX> CLastN = Cx0;
    std::array<float, MaxX> CN{}; // сначала нужно рассчитать
    std::array<float, MaxX> CNextN{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxX; ++i) {
        std::cout << " " << CLastN[i];
    }

    CLastN[MaxX-1] = Cx0[MaxX-1];
    CN[MaxX-1] =  Cx0[MaxX-1];

    std::cout << std::endl << "n1 : ";
    std::cout << " " << CN[MaxX-1];
    for (int i{MaxX-2}; i >= 0; --i) {
        CN[i] =  CLastN[i] + a*(CLastN[i+1] - CLastN[i]); // правый
        std::cout << " " << CN[i];
    }
    for (int n = 1; n < MaxN; ++n) {
        std::cout << std::endl << "n" << n << ": ";
        std::cout << " " << 0;

        CNextN[MaxX-1] =  0;

        for (int i{MaxX-2}; i >= 0; --i) {
            CNextN[i] = CN[i] - CN[i+1] + CLastN[i+1] + 2 * a * (CN[i+1] - CN[i]);
            std::cout << " " << CNextN[i];
        }

        CLastN = CN;
        CN = CNextN;
    }
    for (int i{}; i < MaxX; ++i) {
        points.emplace_back(i, CNextN[i]);
    }

    return points;
}

std::vector<GraphWindow::Point> Lab2::lincomb(std::array<float, MaxX> Cx0, float a) {
    std::vector<GraphWindow::Point> points;

    std::array<float, MaxX> CLastN = Cx0;
    std::array<float, MaxX> CN{}; // сначала нужно рассчитать
    std::array<float, MaxX> CNextN{};

    std::cout << std::endl << "n0 : ";
    for (int i{}; i < MaxX; ++i) {
        std::cout << " " << CLastN[i];
    }

    CLastN[MaxX-1] = 0;
    CN[MaxX-1] =  0;

    std::cout << std::endl << "n1 : ";
    std::cout << " " << CN[MaxX-1];
    for (int i{MaxX-2}; i >= 0; --i) {
        CN[i] =  CLastN[i] + a*(CLastN[i+1] - CLastN[i]); // правый
        std::cout << " " << CN[i];
    }

    for (int n = 1; n < MaxN; ++n) {
        std::cout << std::endl << "n" << n << ": ";
        std::cout << " " << 0;

        CNextN[MaxX-1] =  0;
        CN[0] = 0;

        for (int i{MaxX-2}; i >= 1; --i) {
            CNextN[i] = CN[i] - (CN[i+1] - CLastN[i+1])/2 - a * (CN[i-1] + 4 * CN[i] - 5 * CN[i+1])/4;
            std::cout << " " << CNextN[i];
        }

        CLastN = CN;
        CN = CNextN;
    }
    for (int i{}; i < MaxX; ++i) {
        points.emplace_back(i, CNextN[i]);
    }

    return points;
}
