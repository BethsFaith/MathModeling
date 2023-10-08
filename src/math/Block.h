//
// Created by VerOchka on 30.09.2023.
//

#ifndef LAB1_KOSHI_BLOCK_H
#define LAB1_KOSHI_BLOCK_H

#include <iostream>
#include <vector>
#include <map>

#include "Operations.h"

class Block {
public:
    enum Type {
        VALUE, VARIABLE, UNARY, BINARY
    };

    Block() = default;
    Block(Block const &block) = default;

    double value{};
    std::string variable;
    Unary unary;
    Binary binary;
    Type type;
};

#endif //LAB1_KOSHI_BLOCK_H
