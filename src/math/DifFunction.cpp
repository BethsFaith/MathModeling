//
// Created by VerOchka on 08.10.2023.
//

#include "DifFunction.h"

DifFunction::DifFunction(const std::string &function, std::string argument) : Function(function, argument) {
}

double DifFunction::getValue(double x, bool &success) {
    if (x == 0)
        return last_y;

    double res;

    _expression.setArgument(_argument, last_y);
    success = _expression.consider(res);

    last_y = res;

    return res;
}

bool DifFunction::isWholeNumber(double num) {
    return std::fmod(num, 1) == 0;
}

void DifFunction::setVariable(const std::string &variable, double value) {
    _expression.setArgument(variable, value);
}

