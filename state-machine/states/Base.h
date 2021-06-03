//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H

#include "state-machine/states/CreateVariable.h"
#include "state-machine/states/VariableAssigment.h"
#include "state-machine/states/Error.h"

class Base : public State {
    std::string buffer;
public:
    Base(Stack &stack) : State(stack) {
        buffer = "";
    }

    State *parse(const std::string &text, int position) override {
        if (!Utility::whitespace(text[position])) {
            std::cout << text[position];
            buffer.push_back(text[position]);
            return this;
        }

        if (buffer == "mat") {
            return new CreateVariable$NameState(stack_);
        }

        Token *token = Utility::find_token(stack_, buffer);
        if (token) {
            return new VariableAssigment(stack_, (Variable *) token);
        }

        std::cout << "buffer: " << buffer << "\n";
        return new Error("Token not found: " + buffer, stack_);
    }

};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H
