//
// Created by mateusz on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H

#include "Token.h"
#include "../Matrix.h"

using ValueType = Matrix;

class Variable : public Token {
public:
    Variable(std::string name, ValueType value)
            : name_(std::move(name)), value_(std::move(value)) {}

    std::string &GetName() override;

    TokenType GetType() override;

    void SetValue(Matrix value) {
        value_ = std::move(value);
    }

    Matrix& GetValue();

private:
    ValueType value_;
    std::string name_;
};


#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H
