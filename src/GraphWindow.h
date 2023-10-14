//
// Created by VerOchka on 08.10.2023.
//

#ifndef LAB1_KOSHI_GRAPHWINDOW_H
#define LAB1_KOSHI_GRAPHWINDOW_H

#include <algorithm>

#include "Window.h"
#include "math/Utilities.h"

class GraphWindow : public Window{
public:
    struct Point {
        float x;
        float y;
    };
    struct DrawableFunction {
          std::vector<Point> points;
          sf::Color color;
          std::string name;
    };

    GraphWindow(int width, int height, const char* title, Color backgroundColor, Color cAxes);

    void start() override;

    void setView(double xOffset, double yOffset);

    void dragging();

    void addFunction(const std::vector<Point> &points, const std::string &name, Color color);

    void setAxesStep(double axesStep);

protected:
    void update(double deltaTime) override;
    void display() override;

    void drawAxes();
    void construct(DrawableFunction &function);

    bool onScreen(int cX, int cY) const;
    int toCrdX(double x) const;
    int toCrdY(double y) const;

    static const int defaultSegSize = 128;
    static const int maxSegSize = 250;
    static const int minSegSize = 15;
private:
    double _axesStep{};
    double _scaleX{};
    double _scaleY{};
    double _xOffset{};
    double _yOffset{};

    sf::Color _axisColor;
    std::vector<DrawableFunction> _functions;
    int _curFunctionIndex;
};


#endif //LAB1_KOSHI_GRAPHWINDOW_H
