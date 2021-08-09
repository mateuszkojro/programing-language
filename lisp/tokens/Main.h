#ifndef LS_MAIN
#define LS_MAIN

#include "../Stack.h"

#include "Scope.h"
#include "Token.h"

class Main : public Token
{
public:
    Main() { LOG_STATE("Main"); };
    ~Main() override = default;
    Token *parse(char znak, Stack<Token *> &stack) override;
};

#endif