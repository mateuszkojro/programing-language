#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <string>
#include "tokens/Variable.h"
#include "state-machine/Parser.h"

int hello(Stack& stack){
    std::cout << "hellooooooooooooooooooooooooooooooooooo" << std::endl;
    return 0;
}

int main() {
    Parser parser;
    std::function<int(Stack&)> func = hello;
    parser.stack_.push_back(new Function("print",func));
    parser.parse_string("mat x = [[1]];"
                        "x = null;"
                        "print()"
    );
    return 0;
}
