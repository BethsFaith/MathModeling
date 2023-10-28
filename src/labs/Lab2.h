//
// Created by VerOchka on 27.10.2023.
//

#ifndef LAB1_KOSHI_LAB2_H
#define LAB1_KOSHI_LAB2_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>
#include <complex>

#include "../GraphWindow.h"
#include "../math/DifFunction.h"

class Lab2 {
public:
    static void work(int width, int height);

private:
    static const int MaxX = 100;
    static const int MaxN = 300;

    static std::vector<GraphWindow::Point> left(std::array<float, MaxX> Cx, float a);
    static std::vector<GraphWindow::Point> right(std::array<float, MaxX> Cx, float a);
    static std::vector<GraphWindow::Point> center(std::array<float, MaxX> Cx, float a);
};


#endif //LAB1_KOSHI_LAB2_H
