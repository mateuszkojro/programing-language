#ifndef LS_VARIABLE
#define LS_VARIABLE

#include "../Stack.h"

#include "Token.h"
#include "Scope.h"

class Variable : public Token
{
public:
    Variable() { LOG_STATE("Variable"); };
    virtual ~Variable() = default;

    Token *parse(char znak, Stack<Token *> &stack) override;

private:
    std::string name_;
    // Matrix* value_;
};

#endif