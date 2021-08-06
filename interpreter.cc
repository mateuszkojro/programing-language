#include <iostream>
#include <string>
#include <map>

#include "lisp/lisp.h"

int run_interpreter(ls::Interpreter& i){
    
    std::string line;
    do {
    
        std::getline(std::cin, line);
        i.interpret(line);

    } while (line != "q" || line == "quit");
    
    return 0;
}

void print_help(){
    std::cout << "This is help!" << std::endl;
}

int main(int argc, char **argv)
{
    ls::Interpreter i;
    switch (argc){
        case 1:
            return run_interpreter(i);
            break;
        case 2:
            return i.interpret(argv[1]);
            break;
        default:
            print_help();
            return 1;
            break;
    }
}
