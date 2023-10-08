//
// Created by VerOchka on 30.09.2023.
//

#ifndef LAB1_KOSHI_OPERATIONS_H
#define LAB1_KOSHI_OPERATIONS_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <map>

#include "Utilities.h"

typedef bool(*Unary)(double &, double);
typedef bool(*Binary)(double &, double, double);

namespace Operations {
    bool unaryPlus(double& res, double arg);
    bool unaryMinus(double& res, double arg);
    bool absMy(double& res, double arg);
    bool sqrtMy(double& res, double arg);
    bool lnMy(double& res, double arg);
    bool lgMy(double& res, double arg);
    bool logMy(double& res, double arg);
    bool sinMy(double& res, double arg);
    bool cosMy(double& res, double arg);
    bool tgMy(double& res, double arg);
    bool ctgMy(double& res, double arg);
    bool arcsinMy(double& res, double arg);
    bool arccosMy(double& res, double arg);
    bool arctgMy(double& res, double arg);
    bool arcctgMy(double& res, double arg);

    bool addition(double& res, double a, double b);
    bool subtraction(double& res, double a, double b);
    bool multiplication(double& res, double a, double b);
    bool division(double& res, double a, double b);
    bool modulo(double& res, double a, double b);
    bool exponentiation(double& res, double a, double b);

    class Definition {
    public:
        static std::map<std::string, Unary> unaryFuncs;
        static std::map<std::string, Binary> binaryFuncs;

        static void init();
    };
}

#endif //LAB1_KOSHI_OPERATIONS_H
