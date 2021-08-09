#include "Main.h"

Token *Main::parse(char znak, Stack<Token *> &stack)
{
    if (znak == '(')
    {
        // New scope
        auto scope = new Scope();
        stack.push(scope);
        return scope;
    }

    if (is_whitespace(znak))
    {
        // dont change anything go on
        return this;
    }
    
    return this;
}