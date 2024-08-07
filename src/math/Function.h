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

#include "Sequence.h"

class Function {
public:
    explicit Function(const std::string &function, std::string argument);
    virtual ~Function() = default;

    virtual double getValue(double x, bool &success);

    std::string getArgument();
    void setVariable(const std::string &variable, double value);
protected:
    Sequence _expression;
    std::string _argument;
};


#endif //LAB1_KOSHI_FUNCTION_H
