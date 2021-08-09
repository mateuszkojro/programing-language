#include "Variable.h"

Token *Variable::parse(char znak, Stack<Token *> &stack)
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
        name_ = buffer_;
        return this;
    }
    
    buffer_ += znak;
    return this;
}