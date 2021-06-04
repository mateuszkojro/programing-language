//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H

#include <cassert>
#include <string>
#include <vector>
#include <deque>

#include "Token.h"
#include "State.h"
#include "Utility.h"


class Matrix {
public:

    static bool parse_matrix(const std::string &code, Matrix &matrix);

    static bool is_matrix(const std::string buffer) {

        return (buffer[0] == '[' && buffer[1] == '[') || buffer == "null" ;
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


#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_MATRIX_H
