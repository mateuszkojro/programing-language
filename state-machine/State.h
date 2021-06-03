//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_H

#include <deque>
#include "tokens/Token.h"

class State {
public:
    State(Stack &stack) : stack_(stack) {}

    virtual State *parse(const std::string &text, int position) = 0;

protected:
    Stack &stack_;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_STATE_H
