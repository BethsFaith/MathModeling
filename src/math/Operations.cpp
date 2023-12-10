//
// Created by VerOchka on 30.09.2023.
//

#include "Operations.h"

namespace Operations {
    bool unaryPlus(double &res, double arg) {
        res = arg;
        return true;
    }

    bool unaryMinus(double &res, double arg) {
        res = -arg;
        return true;
    }

    bool absMy(double &res, double arg) {
        res = abs(arg);
        return true;
    }

    bool sqrtMy(double &res, double arg) {
        if (arg >= 0) {
            res = sqrt(arg);
            return true;
        }
        return false;
    }

    bool lnMy(double &res, double arg) {
        if (arg > 0) {
            res = log(arg);
            return true;
        }
        return false;
    }

    bool lgMy(double &res, double arg) {
        if (arg > 0) {
            res = log10(arg);
            return true;
        }
        return false;
    }

    bool logMy(double &res, double arg) {
        if (arg > 0) {
            res = log2(arg);
            return true;
        }
        return false;
    }

    bool sinMy(double &res, double arg) {
        res = sin(arg);
        return true;
    }

    bool cosMy(double &res, double arg) {
        res = cos(arg);
        return true;
    }

    bool tgMy(double &res, double arg) {
        if (!Utilities::equal(fmod(arg + M_PI_2, M_PI), 0)) {
            res = tan(arg);
            return true;
        }
        return false;
    }

    bool ctgMy(double &res, double arg) {
        if (!Utilities::equal(fmod(arg, M_PI), 0)) {
            res = 1 / tan(arg);
            return true;
        }
        return false;
    }

    bool arcsinMy(double &res, double arg) {
        if (-1 <= arg && arg <= 1) {
            res = asin(arg);
            return true;
        }
        return false;
    }

    bool arccosMy(double &res, double arg) {
        if (-1 <= arg && arg <= 1) {
            res = acos(arg);
            return true;
        }
        return false;
    }

    bool arctgMy(double &res, double arg) {
        res = atan(arg);
        return true;
    }

    bool arcctgMy(double &res, double arg) {
        res = atan(-arg) + M_PI_2;
        return true;
    }

    bool addition(double &res, double a, double b) {
        res = a + b;
        return true;
    }

    bool subtraction(double &res, double a, double b) {
        res = a - b;
        return true;
    }

    bool multiplication(double &res, double a, double b) {
        res = a * b;
        return true;
    }

    bool division(double &res, double a, double b) {
        if (!Utilities::equal(b, 0)) {
            res = a / b;
            return true;
        }
        return false;
    }

    bool modulo(double &res, double a, double b) {
        if (!Utilities::equal(b, 0)) {
            res = fmod(a, b);
            return true;
        }
        return false;
    }

    bool exponentiation(double &res, double a, double b) {
        res = pow(a, b);
        return true;
    }

    std::map<std::string, Unary> Definition::unaryFuncs{};
    std::map<std::string, Binary> Definition::binaryFuncs{};

    void Definition::init() {
        unaryFuncs["plus"] = &unaryPlus;
        unaryFuncs["minus"] = &unaryMinus;
        unaryFuncs["abs"] = &absMy;
        unaryFuncs["sqrt"] = &sqrtMy;
        unaryFuncs["ln"] = &lnMy;
        unaryFuncs["lg"] = &lgMy;
        unaryFuncs["log"] = &logMy;
        unaryFuncs["sin"] = &sinMy;
        unaryFuncs["cos"] = &cosMy;
        unaryFuncs["tg"] = &tgMy;
        unaryFuncs["ctg"] = &ctgMy;
        unaryFuncs["asin"] = &arcsinMy;
        unaryFuncs["accos"] = &arccosMy;
        unaryFuncs["atg"] = &arctgMy;
        unaryFuncs["actg"] = &arcctgMy;
        binaryFuncs["+"] = &addition;
        binaryFuncs["-"] = &subtraction;
        binaryFuncs["*"] = &multiplication;
        binaryFuncs["/"] = &division;
        binaryFuncs["%"] = &modulo;
        binaryFuncs["^"] = &exponentiation;
    }
}