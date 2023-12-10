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

    void setXPrecision(int xPrecision);
    void setYPrecision(int yPrecision);
    void setXStep(double xStep);
    void setYStep(double yStep);
    void setXOffset(double xOffset);
    void setYOffset(double yOffset);
    void setYScale(double yScale);
    void setXScale(double xScale);

    void clean();

protected:
    void update(double deltaTime) override;
    void display() override;

    void drawAxes();
    void construct(DrawableFunction &function);

    bool onScreen(int cX, int cY) const;
    int toCrdX(double x) const;
    int toCrdY(double y) const;

    static const int defaultSegSize = 500;
    static const int maxSegSize =  4000;
    static const int minSegSize = 15;
private:
    double _xStep{};
    double _yStep{};
    double _xScale{};
    double _yScale{};
    double _xOffset{};
    double _yOffset{};

    int _xPrecision{3};
    int _yPrecision{3};

    sf::Color _axisColor;

    double _lastDeltaTime;

    std::vector<DrawableFunction> _functions;
    int _curFunctionIndex;
};


#endif //LAB1_KOSHI_GRAPHWINDOW_H
