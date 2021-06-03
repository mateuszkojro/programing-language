//
// Created by mateusz on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H

#include "tokens/Token.h"
#include "Matrix.h"

using ValueType = Matrix;

class Variable : public Token {
public:
    Variable(std::string name, ValueType value)
            : name_(std::move(name)), value_(std::move(value)) {}

    std::string &get_name() override {
        return name_;
    }

    TokenType get_type() override {
        return TokenType::variable;
    }

    void set_value(Matrix value) {
        value_ = std::move(value);
    }

    Matrix get_value() {
        return value_;
    }

private:
    Matrix value_;
    std::string name_;
};


#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H
