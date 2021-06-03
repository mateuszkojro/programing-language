#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <string>
#include "tokens/Variable.h"
#include "state-machine/Parser.h"

int main() {
    Parser parser;
    Matrix matrix;
    Matrix::parse_matrix("[[1]]", matrix);
    parser.stack_.push_back(new Variable("x", matrix));
    parser.parse_string("x = [[1,2,3]];");
    return 0;
}
