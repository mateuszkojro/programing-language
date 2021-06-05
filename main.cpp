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
    Variable *variable = (Variable *) stack.back();
    stack.pop_back();

    std::cout << variable->get_value().repr() << std::endl;
    return 0;
}

int ones(Stack &stack) {
    Matrix m;
    Matrix::parse_matrix("[[1,1,1][1,1,1][1,1,1]]", m);
    stack.push_back(new Variable("return", m));
    return 1;
}

int main(int argc, char **argv) {
    Parser parser;
//    std::function<int(Stack&)> func = hello;
    parser.stack_.push_back(new Function("hello", hello));
    parser.stack_.push_back(new Function("exit", exit_func));
    parser.stack_.push_back(new Function("print", print));
    parser.stack_.push_back(new Function("ones", ones));

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
