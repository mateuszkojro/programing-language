#ifndef LS_TOKEN
#define LS_TOKEN

#include <iostream>

#include "../Stack.h"

#include "../utils/parsing.h"

#define LOG_STATE(state) (std::cerr << state << std::endl)

class Token
{
public:
    Token() = default;
    virtual ~Token() = default;

    virtual Token *parse(char znak, Stack<Token *> &stack) = 0;

protected:
    std::string buffer_;
};

#endif