#ifndef LS_FUNCTION
#define LS_FUNCTION

#include "../Stack.h"

#include "Token.h"

class Function : public Token
{
public:
    Function() = default;
    ~Function() override = default;

private:
    Stack<Token *> arguments_;
};

#endif