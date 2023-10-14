//
// Created by VerOchka on 08.10.2023.
//

#ifndef LAB1_KOSHI_GRAPHWINDOW_H
#define LAB1_KOSHI_GRAPHWINDOW_H

#include "../src/Window.h"
#include "../src/math/Function.h"
#include "../src/math/Utilities.h"

class GraphicWindow : public Window{
public:
    GraphicWindow(int width, int height, const char* title, Color backgroundColor, Color cAxes);

    void start() override;

    void setView(double offsetX, double offsetY);

    void addFunction(Function& func, Color color);

protected:
    void update(double deltaTime) override;
    void display() override;

    void dragging();
    void drawAxes();
    void construct(Function& func, sf::Color color);
    void graphMark();

    bool onScreen(int cX, int cY) const;
    double toMathX(int x) const;
    double toMathY(int y) const;
    int toCrdX(double x) const;
    int toCrdY(double y) const;

    static const int defaultSegSize = 128;
private:
    int _curMark{};
    double _scale{}; //pixels per unit
    double _axesStep{};
    int _axesPrecision{};
    double _xOffset{};
    double _yOffset{};

    std::vector<std::pair<Function, sf::Color>> _funcs;
    sf::Color _axisColor;
};


#endif //LAB1_KOSHI_GRAPHWINDOW_H
