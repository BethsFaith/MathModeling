#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Graph");
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
