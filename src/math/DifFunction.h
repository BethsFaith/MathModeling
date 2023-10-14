//
// Created by VerOchka on 08.10.2023.
//

#ifndef LAB1_KOSHI_DIFFUNCTION_H
#define LAB1_KOSHI_DIFFUNCTION_H

#include "Function.h"

class DifFunction : public Function{
public:
    DifFunction(const std::string &function, std::string argument);
    ~DifFunction() override = default;

    double getValue(double x, bool &success) override;

    bool isWholeNumber(double num);
private:
    float last_y = 1;
};

#endif //LAB1_KOSHI_DIFFUNCTION_H
