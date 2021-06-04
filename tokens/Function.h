//
// Created by mateu on 6/4/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTION_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTION_H

#include <string>
#include <functional>
#include <utility>
#include "Token.h"

#define FUNCTION std::function<int(Stack&)>

class Function : public Token {
    std::string name_;

    FUNCTION function_;

public:
    Function(std::string name, FUNCTION function)
            : name_(std::move(name)), function_(std::move(function)) {};

    const std::string &get_name() override {
        return name_;
    }

    TokenType get_type() override {
        return function;
    }

    FUNCTION get_value() {
        return function_;
    }

};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTION_H
