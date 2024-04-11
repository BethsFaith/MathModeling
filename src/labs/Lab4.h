//
// Created by VerOchka on 10.12.2023.
//

#ifndef LAB1_KOSHI_LAB4_H
#define LAB1_KOSHI_LAB4_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>
#include <complex>
#include <cstdlib>

#include "../GraphWindow.h"
#include "../math/DifFunction.h"

#define PI 3.14159265358979323846

class Lab4 {
public:
    static void work(int width, int height);
private:
    static const int N = 100;
    static constexpr double T = 25;
    static constexpr float ht = 0.1f;
    static constexpr float hx = 1.0f;
    static constexpr float alfa= 0;
    static constexpr float beta = 0;

    static std::vector<GraphWindow::Point> convectionDiffusion(std::array<float, N + 1> q);
};

#endif //LAB1_KOSHI_LAB4_H
