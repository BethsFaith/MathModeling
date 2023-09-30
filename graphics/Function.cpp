//
// Created by VerOchka on 30.09.2023.
//

#include "Function.h"

Function::Function(const std::string& function) {
    pullFunction(function);
}

void Function::pullFunction(const std::string& function) {
    // 1) найти последние скобочки
    std::vector<int> braces_indexes;

    for (int i{}; i < function.size(); ++i) {
        if (function.at(i) == '(') {
            braces_indexes.push_back(i);
        }
    }

    std::sort(braces_indexes.begin(), braces_indexes.end(), [] (int x, int y) {
        if (x > y) return true;
    });

    // 2)
}

void Function::pullExpression(const std::string &expression) {

}

void Function::setOperation(const std::string &operation, Function::Expression &expression) {
    if (operation == "root") {
        expression.operation = sqrt;
    }
}

float Function::getValue(float x) {
    return 0;
}
