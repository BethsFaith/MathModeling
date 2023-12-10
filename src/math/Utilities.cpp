//
// Created by VerOchka on 30.09.2023.
//

#include "Utilities.h"

namespace Utilities {
    std::string dtos(double val, int precision) {
        char buffer[20];
        std::string format = std::string("%.") + std::to_string(precision) + std::string("f");
        sprintf_s(buffer, format.c_str(), val);
        return buffer;
    }

    bool equal(double a, double b) {
        return abs(a - b) < eps;
    }

    double getCloseLowerNum(double num, double val) {
        int l = -1e9;
        int r = 1e9;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (num < mid * val)
                r = mid;
            else
                l = mid;
        }
        return val * l;
    }

    std::string substr(const std::string& str, int l, int r)
    {
        return str.substr(l, r - l + 1);
    }

    void line(sf::Image& image, int x1, int y1, int x2, int y2, sf::Color color)
    {
        int w = abs(x2 - x1);
        int h = abs(y2 - y1);
        bool swapAxes = w < h;
        if (swapAxes)
        {
            std::swap(x1, y1);
            std::swap(x2, y2);
        }
        if (x2 < x1)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }
        bool isAddY = y1 < y2;
        double k = w ? (double)h / w : 0;
        double curY = y1;
        int y = y1;
        for (int x = x1; x <= x2; x++)
        {
            if (abs(curY - y) > 0.5)
                y += isAddY ? 1 : -1;
            image.setPixel(swapAxes ? y : x, swapAxes ? x : y, color);
            curY += isAddY ? k : -k;
        }
    }

    void drawLine(sf::RenderWindow &window, int x1, int y1, int x2, int y2, sf::Color color, int width)
    {
//        sf::Vertex line[] =	{sf::Vertex(sf::Vector2f(x1, y1), color),
//                                sf::Vertex(sf::Vector2f(x2 + 1, y2 + 1), color) };
//
//        window.draw(line, 2, sf::Lines);
//        window.draw(line, 2, sf::Lines);
//        window.draw(line, 2, sf::Lines);
//        window.draw(line, 2, sf::Lines);

        sf :: Vector2f a , b;
        sf :: ConvexShape ln;
        sf :: CircleShape A , B;

        float length = sqrt (pow(x1 - x2 , 2 ) + pow( y1 - y2, 2 ) );
        float rot = atan2 ( x2 -x1 , y2 - y1);
        float X1 , Y1 , X2 , Y2;
        X1 = sin( rot + 1.570796 ) * ( width / 2 ); // + 90°
        Y1 = cos( rot + 1.570796 ) * ( width / 2 ); // + 90°
        X2 = sin( rot + 4.712388 ) * ( width / 2 ); // + 270°
        Y2 = cos( rot + 4.712388 ) * ( width / 2 ); // + 270°

        A = sf :: CircleShape( width / 2 , 20 );
        B = sf :: CircleShape( width / 2 , 20 );
        A . setPosition ( x1 - width / 2 , y1 - width / 2 );
        B . setPosition ( x2 - width / 2 , y2 - width / 2 );
        A . setFillColor( color);
        A . setFillColor( color);

        ln . setPointCount ( 4 );
        ln . setPoint ( 0 , sf::Vector2f(x1,y1)+ sf :: Vector2f ( X1 , Y1 ) );
        ln . setPoint ( 1 , sf::Vector2f(x1,y1) + sf :: Vector2f ( X2 , Y2 ) );
        ln . setPoint ( 2 , sf::Vector2f(x2,y2) + sf :: Vector2f ( X2 , Y2 ) );
        ln . setPoint ( 3 , sf::Vector2f(x2,y2) + sf :: Vector2f ( X1 , Y1 ) );
        ln . setFillColor( color);

        window.draw(ln);
        window.draw(A);
        window.draw(B);
    }

    void setPixel(sf::RenderWindow& window, int x, int y, sf::Color color) {
        drawLine(window, x, y, x, y, color, 0);
    }

    void cursorRestriction(const sf::RenderWindow& window)
    {
        int x = sf::Mouse::getPosition(window).x;
        int y = sf::Mouse::getPosition(window).y;
        int newX = x;
        int newY = y;
        newX = std::min(newX, (int)window.getSize().x - 1);
        newX = std::max(newX, 0);
        newY = std::min(newY, (int)window.getSize().y - 1);
        newY = std::max(newY, 0);
        if (x != newX || y != newY)
            sf::Mouse::setPosition(sf::Vector2i(newX, newY), window);
    }
    bool isCursorInWindow(const sf::RenderWindow& window)
    {
        int x = sf::Mouse::getPosition(window).x;
        int y = sf::Mouse::getPosition(window).y;
        return 0 <= x && x < window.getSize().x && 0 <= y && y < window.getSize().y;
    }
}