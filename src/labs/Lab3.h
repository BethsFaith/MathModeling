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
    static const int MaxX = 100;
    static const int MaxN = 300;
    static constexpr float t = 0.01f;
    static constexpr float h = 1;
    static constexpr float k = 0.1f;
    static constexpr float u = 0.6f;

    static std::vector<GraphWindow::Point> explicitScheme(std::array<float, MaxX> Cx0);
    static std::vector<GraphWindow::Point> implicitScheme(std::array<float, MaxX> Cx0);
    static std::vector<GraphWindow::Point> analyticScheme(std::array<float, MaxX> Cx0);
};


#endif //LAB1_KOSHI_LAB3_H
