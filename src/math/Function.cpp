//
// Created by VerOchka on 30.09.2023.
//

#include "Function.h"

#include <utility>

Function::Function(const std::string &function, std::string argument) : _expression(function), _argument(std::move(argument)) {}

double Function::getValue(double x, bool &success) {
    _expression.setArgument(_argument, x);

    double res;
    success = _expression.consider(res);

    return res;
}

std::string Function::getArgument() {
    return _argument;
}
