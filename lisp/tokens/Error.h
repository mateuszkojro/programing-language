#ifndef LS_ERROR
#define LS_ERROR

#include <string>
#include <cassert>
#include <iostream>
#include <utility>

#include "../Stack.h"

#include "Token.h"

class Error : public Token
{
public:
    Error() = delete;
    Error(std::string message) : message_(std::move(message))
    {
        std::cerr << "ERR:\t" << message_ << std::endl;
        assert(false);
    }

    Token *parse(char znak, Stack<Token *> &stack) override { assert(false); }

    ~Error() override = default;

private:
    std::string message_;
};

#endif