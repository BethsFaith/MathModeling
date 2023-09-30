#include <SFML/Graphics.hpp>
#include <iostream>
#include <wtypes.h>

static void pullDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}

int main() {
    int width, height;
    pullDesktopResolution(width, height);

    sf::RenderWindow window(sf::VideoMode(width, height), "Koshi");
    std::vector<sf::Vertex> points;

    // Главный цикл приложения. Выполняется, пока открыто окно
    while (window.isOpen()) {
        // Обрабатываем очередь событий в цикле
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Пользователь нажал на кнопку (любую)
            if (event.type == sf::Event::KeyPressed) {}
        }
        window.clear();
        window.display();
    }
    return 0;
}
