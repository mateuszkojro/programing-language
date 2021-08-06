#include <iostream>

#include "lisp.h"

namespace ls {

    Interpreter::Interpreter() = default;

    int Interpreter::interpret(const std::string &text)
    {
        std::cout << text << std::endl;
        return 0;
    }
}