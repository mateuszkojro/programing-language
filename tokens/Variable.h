//
// Created by mateusz on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLE_H

#include "tokens/Token.h"

class Matrix {
public:

    static bool is_matrix(const std::string buffer) {
        return buffer[0] == '[' && buffer[1] == '[';
    }

    void add_column() {
        assert(rows == 1);
        cols += 1;
    }

    void add_row() {
        rows += 1;
        assert(cols == streak);
        streak = 0;
    }

    bool add_value(double value) {
        streak += 1;
        if (streak > cols)
            return false;
        data_.push_back(value);
        return true;
    }

    Matrix() : cols(0), rows(0), streak(0) {}

private:
    int streak;
    int cols;
    int rows;
    std::vector<double> data_;
};

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
