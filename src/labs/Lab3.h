//
// Created by VerOchka on 11.11.2023.
//

#ifndef LAB1_KOSHI_LAB3_H
#define LAB1_KOSHI_LAB3_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>
#include <complex>

#include "../GraphWindow.h"
#include "../math/DifFunction.h"

class Lab3 {
public:
    static void work(int width, int height);

private:
    static const int MaxN = 100;
    static constexpr double T = 100;
    static constexpr float ht = 0.1f;
    static constexpr float hx = 1;
    static constexpr float a = 1;

    static std::vector<GraphWindow::Point> explicitScheme(std::array<float, MaxN+1> Cx0);
    static std::vector<GraphWindow::Point> implicitScheme(std::array<float, MaxN+1> Cx0);
    static std::vector<GraphWindow::Point> analyticScheme(std::array<float, MaxN+1> Cx0);
};


#endif //LAB1_KOSHI_LAB3_H
