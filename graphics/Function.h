//
// Created by VerOchka on 30.09.2023.
//

#ifndef LAB1_KOSHI_FUNCTION_H
#define LAB1_KOSHI_FUNCTION_H

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <queue>

typedef bool(*Unary)(double&, double);
typedef bool(*Binary)(double&, double, double);

class Function {
public:
    struct Expression {
        float (*operation)(...);
        std::queue<float> args;
    };

    explicit Function(const std::string& function);
    ~Function() = default;

    float getValue(float x);
private:
    void pullFunction(const std::string& function);
    void pullExpression(const std::string& expression);
    void setOperation(const std::string& operation, Expression &expression);

    std::queue<Expression> _expressions;
};


#endif //LAB1_KOSHI_FUNCTION_H
