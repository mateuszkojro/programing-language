#include "Scope.h"

Token *Scope::parse(char znak, Stack<Token *> &stack)
{

    if (znak == '(')
    {
        // Scopes can be nested
        auto scope = new Scope();
        stack.push(scope);
        return scope;
    }

    if (is_whitespace(znak) && !buffer_.empty())
    {
        if (buffer_ == "mat")
        {
            // creation of the new variable
            auto variable = new Variable;
            stack.push(variable);
            return variable;
        }

        return this;
    }
    
    
    buffer_ += znak;
    return this;
}