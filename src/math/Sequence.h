//
// Created by VerOchka on 30.09.2023.
//

#ifndef LAB1_KOSHI_SEQUENCE_H
#define LAB1_KOSHI_SEQUENCE_H

#include <iostream>

#include "Block.h"

#define M_E 2.71828182845904523536

class Sequence {
public:
    Sequence() = default;

    explicit Sequence(const std::string &expression);

    void setArgument(const std::string &variable, double value);

    bool consider(double &res) const;

protected:
    static int getPrior(const std::string &operation);

    static bool isRightAssoc(const std::string &operation);

    static bool calc(double& res, const std::vector<Block>& sequence, const std::map<std::string, double>& vars);

    static std::vector<Block> toRPN(const std::string &expression);
private:
    std::vector<Block> sequence;
    std::map<std::string, double> variables;
//    void init(const std::string &sequence);

//    std::vector<Expression> _sequence;
//    std::map<std::string, double> _variables;
};

#endif //LAB1_KOSHI_SEQUENCE_H
