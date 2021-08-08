#ifndef LS_LISP
#define LS_LISP

#include <iostream>

#include "Stack.h"
#include "tokens/Token.h"

namespace ls
{
    class Interpreter
    {
    public:
        Interpreter();
        int interpret(const std::string &code);

    private:
        Stack<Token*> stack_;
    };
}

#endif