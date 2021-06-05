//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H


#include "states/CreateVariable.h"
#include "states/VariableAssigment.h"
#include "states/FunctionCall.h"
#include "states/Error.h"
#include "Conditional.h"


class Base : public State {
    std::string buffer;
public:
    Base(Stack &stack) : State(stack) {
        CHANGE_STATE("Base");
    }

    State *parse(const std::string &text, int position) override {
        if (buffer == "mat") {
            buffer = "";
            return new CreateVariable$NameState(stack_);
        }

        if (buffer == "if") {
            return new Conditional(stack_);
        }

        if (text[position] == '}')
            return this;

        if (text[position] == '=') {

            Token *token = Utility::find_token(stack_, buffer);
            if (token != nullptr) {
                return new VariableAssigment(stack_, (Variable *) token);
            }

            return new Error("Token not found: " + buffer, stack_);
        }

        if (text[position] == '(') {
            return new FunctionCall(stack_, buffer, nullptr);
        }

        if (Utility::whitespace(text[position])) {
            return this;
        }

        if (!Utility::whitespace(text[position])) {
            buffer.push_back(text[position]);
            return this;
        }
    }

};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_BASE_H
