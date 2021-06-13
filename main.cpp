#include <iostream>
#include <vector>
#include <fstream>
#include "tokens/Variable.h"
#include "state-machine/Parser.h"

int hello(Stack &stack) {
    std::cout << "hello" << std::endl;
    return 0;
}

int exit_func(Stack &stack) {
    exit(0);
    return 0;
}

int print(Stack &stack) {
    auto mat = Matrix::get_from_stack(stack);
    std::cout << mat.repr() << std::endl;
    return 0;
}

int ones(Stack &stack) {
    Matrix m;
    Matrix::parse_matrix("[[1,1,1][1,1,1][1,1,1]]", m);
    stack.push_back(new Variable("return", m));
    return 1;
}

int input(Stack &stack) {
    Matrix m;
    std::string input;
    std::getline(std::cin, input);
    Matrix::parse_matrix(input, m);
    stack.push_back(new Variable("return", m));
    return 1;
}

int text(Stack &stack) {
    auto val = Matrix::get_from_stack(stack);
    for (int i = 0; i < val.size(); i++) {
        std::cout << (char) val.get(i);
    }
    return 1;
}

int eq(Stack &stack) {
    auto mat1 = Matrix::get_from_stack(stack);
    auto mat2 = Matrix::get_from_stack(stack);

    Matrix m;
    if (mat1 == mat2) {
        Matrix::parse_matrix("[[1]]", m);
    } else {
        Matrix::parse_matrix("[[0]]", m);
    }
    stack.push_back(new Variable("return", m));
    return 1;
}

int newline(Stack &stack) {
    std::cout << std::endl;
    return 1;
}

int not_func(Stack &stack) {
    Matrix val = Matrix::get_from_stack(stack);
    Matrix result;
    for (int i = 0; i < val.size(); i++) {
        result(i) = val(i) == 0 ? 1 : 0;
    }
    stack.push_back(new Variable("return", result));
    return 1;
}

int main(int argc, char **argv) {
    Parser parser;
//    std::function<int(Stack&)> func = hello;
    parser.stack_.push_back(new Function("hello", hello));
    parser.stack_.push_back(new Function("exit", exit_func));
    parser.stack_.push_back(new Function("print", print));
    parser.stack_.push_back(new Function("ones", ones));
    parser.stack_.push_back(new Function("eq", eq));
    parser.stack_.push_back(new Function("input", input));
    parser.stack_.push_back(new Function("text", text));
    parser.stack_.push_back(new Function("newline", newline));


    if (argc < 2) {
        // maybe repl?
        while (true) {
            std::string line;
            std::getline(std::cin, line);
            parser.parse_string(line);
            if (line == "#quit#")
                break;
        }
        return 0;
        std::cerr << "Give file as parametr" << std::endl;
    }

    std::fstream (file);

    file.open(argv[1], std::ios::in);

    while (file.good()) {
        std::string line;
        std::getline(file, line);
        parser.parse_string(line);
    }
//
//    parser.parse_string("mat x = [[1]];"
//                        "x = [[1,2,3,4][5,6,7,8]];"
//                        "hello()"
//    );
    return 0;
}
