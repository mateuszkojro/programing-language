#include <iostream>

#include "Stack.h"

namespace ls
{
    class Interpreter
    {
    public:
        Interpreter();
        int interpret(const std::string &code);

    private:
        Stack<int> stack_;
    };
}
