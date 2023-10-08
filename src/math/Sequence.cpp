//
// Created by VerOchka on 30.09.2023.
//

#include "Sequence.h"

Sequence::Sequence(const std::string &expr) {
    sequence = toRPN(expr);
    variables["e"] = M_E;
}

void Sequence::setArgument(const std::string &variable, double value) {
    variables[variable] = value;
}

bool Sequence::consider(double &res) const {
    return calc(res, sequence, variables);
}

int Sequence::getPrior(const std::string &operation) {
    if (operation == "+" || operation == "-")
        return 1;
    if (operation == "*" || operation == "/")
        return 2;
    if (operation == "^")
        return 3;

    return 4;
}

bool Sequence::isRightAssoc(const std::string &operation) {
    return operation == "^";
}

std::vector<Block> Sequence::toRPN(const std::string &expression) {
    std::vector<Block> res;
    std::vector<std::string> opers;
    bool mayUnary = 1;

    using namespace Operations;
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == '(') {
            opers.push_back("(");
            mayUnary = 1;
            continue;
        }
        if (expression[i] == ')') {
            while (opers.back() != "(") {
                Block block;
                block.type = Block::Type::BINARY;
                block.binary = Definition::binaryFuncs[opers.back()];
                res.push_back(block);
                opers.pop_back();
            }
            opers.pop_back();
            while (!opers.empty() && opers.back() != "(" && getPrior(opers.back()) == 4) {
                Block block;
                block.type = Block::Type::UNARY;
                block.unary = Definition::unaryFuncs[opers.back()];
                res.push_back(block);
                opers.pop_back();
            }
            mayUnary = 0;
            continue;
        }
        int it = i + 1;
        if (isdigit(expression[i]) || expression[i] == '.') {
            while (it < expression.size() && (isdigit(expression[it]) || expression[it] == '.'))
                it++;
        }
        if (isalpha(expression[i])) {
            while (it < expression.size() && isalpha(expression[it]))
                it++;
        }
        std::string blockStr = Utilities::substr(expression, i, it - 1);
        i = it - 1;
        if (isdigit(blockStr[0]) || blockStr[0] == '.') {
            Block block;
            auto s = stod(blockStr);
            block.type = Block::Type::VALUE;
            block.value = s;
            res.push_back(block);
            while (!opers.empty() && opers.back() != "(" && getPrior(opers.back()) == 4) {
                block.type = Block::Type::UNARY;
                block.value = 0;
                block.unary = Definition::unaryFuncs[opers.back()];
                res.push_back(block);
                opers.pop_back();
            }
            mayUnary = 0;
            continue;
        }
        if (mayUnary && blockStr == "+")
            blockStr = "plus";
        if (mayUnary && blockStr == "-")
            blockStr = "minus";
        if (!Definition::unaryFuncs.count(blockStr) && !Definition::binaryFuncs.count(blockStr)) {
            Block block;
            block.type = Block::Type::VARIABLE;
            block.variable = blockStr;
            res.push_back(block);
            while (!opers.empty() && opers.back() != "(" && getPrior(opers.back()) == 4) {
                block.type = Block::Type::UNARY;
                block.variable = "";
                block.unary = Definition::unaryFuncs[opers.back()];
                res.push_back(block);
                opers.pop_back();
            }
            mayUnary = 0;
            continue;
        }
        if (getPrior(blockStr) != 4) {
            while (!opers.empty() && opers.back() != "(" &&
                   (isRightAssoc(blockStr) && getPrior(blockStr) < getPrior(opers.back())
                    || !isRightAssoc(blockStr) && getPrior(blockStr) <= getPrior(opers.back()))) {
                Block block;
                block.type = Block::Type::BINARY;
                block.binary = Definition::binaryFuncs[opers.back()];
                res.push_back(block);
                opers.pop_back();
            }
        }
        mayUnary = 1;
        opers.push_back(blockStr);
    }
    while (!opers.empty()) {
        Block block;
        block.type = Block::Type::BINARY;
        block.binary = Definition::binaryFuncs[opers.back()];
        res.push_back(block);
        opers.pop_back();
    }
    return res;
}

bool Sequence::calc(double &res, const std::vector<Block> &sequence, const std::map<std::string, double> &vars) {
    std::vector<double> stck;
    for (int i = 0; i < sequence.size(); i++) {
        if (sequence[i].type == Block::VALUE)
            stck.push_back(sequence[i].value);
        if (sequence[i].type == Block::VARIABLE)
            stck.push_back(vars.at(sequence[i].variable));
        if (sequence[i].type == Block::UNARY) {
            double x = stck.back();
            stck.pop_back();
            double res;
            if (!sequence[i].unary(res, x))
                return 0;
            stck.push_back(res);
        }
        if (sequence[i].type == Block::BINARY) {
            double b = stck.back();
            stck.pop_back();
            double a = stck.back();
            stck.pop_back();
            double res;
            if (!sequence[i].binary(res, a, b))
                return 0;
            stck.push_back(res);
        }
    }
    res = stck[0];

    return 1;
}