#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>

#include "GraphWindow.h"
#include "math/DifFunction.h"

static void pullDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}

int main() {
    Operations::Definition::init();

    int width, height;
    pullDesktopResolution(width, height);

    GraphWindow window(width, height, "Koshi", Color::WHITE, Color::GREEN);

//    /*явная схема*/ {
//        std::vector<Function> funcs;
//        float t = 1.5;
//        float y0 = 1;
//
//        float a = y0 - t;
//        for (int i = 1; i < 4; ++i) {
//            // yn+1 = yn * a
//            float y = y0*a;
//            std::string expr = std::to_string(y);
//            y0 = y;
//
//            Function function(expr, "x");
////            window.addFunction(function, (Color)i);
//        }
//
////        window.addFunction(function, Color::GREY);
//    }

    DifFunction function("-2*x", "x");
    std::vector<GraphWindow::Point> points;
    bool res;

    points.emplace_back(0, 1);
    for (int i{1}; i < 5; ++i) {
        auto y = function.getValue(i, res);
        if (res) {
            points.emplace_back(i, y);
        }
    }

    window.addFunction(points, "-2*x", GREY);
    window.start();

    return 0;
}
