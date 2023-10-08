#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>

#include "GraphWindow.h"

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

    Function function("cos(3*x)+sin(x)", "x");
    window.addFunction(function, Color::GREY);

    window.start();
    std::vector<sf::Vertex> points;

    return 0;
}
