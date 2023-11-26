//
// Created by VerOchka on 11.11.2023.
//

#ifndef LAB1_KOSHI_LAB3_H
#define LAB1_KOSHI_LAB3_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>
#include <complex>
#include <cstdlib>

#include "../GraphWindow.h"
#include "../math/DifFunction.h"

#define PI 3.14159265358979323846

class Lab3 {
public:
    static void work(int width, int height);

private:
    static const int MaxN = 100;
    static constexpr double T = 100;
    static constexpr float ht = 0.1f;
    static constexpr float hx = 1;
    static constexpr float k = 1;

    static std::vector<GraphWindow::Point> explicitScheme(std::array<float, MaxN+1> Cx0);
    static std::vector<GraphWindow::Point> implicitScheme(std::array<float, MaxN+1> Cx0);
    static std::vector<GraphWindow::Point> analyticScheme(Function &f1, Function &f2);

    template <typename T> static int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
};


#endif //LAB1_KOSHI_LAB3_H
