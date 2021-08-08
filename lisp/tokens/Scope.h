#ifndef LS_SCOPE
#define LS_SCOPE

#include "Token.h"

class Scope : public Token
{
public:
    Scope() = default;
    virtual ~Scope() = default;
};

#endif LS_SCOPE