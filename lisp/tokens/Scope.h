#ifndef LS_SCOPE
#define LS_SCOPE

#include "Token.h"
#include "Variable.h"

#include "Error.h"

class Scope : public Token
{
public:
    Scope() { LOG_STATE("Scope"); };
    virtual ~Scope() = default;

    Token *parse(char znak, Stack<Token *> &stack) override;
};

#endif