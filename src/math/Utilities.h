//
// Created by VerOchka on 30.09.2023.
//

#ifndef LAB1_KOSHI_UTILITIES_H
#define LAB1_KOSHI_UTILITIES_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

namespace Utilities {
    std::string dtos(double val, int precision);
    std::string substr(const std::string& str, int l, int r);

    const double eps = 1e-9;
    bool equal(double a, double b);
    double getCloseLowerNum(double num, double val);

    void line(sf::Image& image, int x1, int y1, int x2, int y2, sf::Color color);

    void line(sf::RenderWindow& window, int x1, int y1, int x2, int y2, sf::Color color);
    void setPixel(sf::RenderWindow& window, int x, int y, sf::Color color);

    void cursorRestriction(const sf::RenderWindow& window);
    bool isCursorInWindow(const sf::RenderWindow& window);
};


#endif //LAB1_KOSHI_UTILITIES_H
