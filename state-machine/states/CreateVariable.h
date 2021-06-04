//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H

#include "../State.h"
#include "Base.h"
#include "Error.h"

class CreateVariable$ValueState : public State {
    std::string name_;
    std::string buffer;
public:
    CreateVariable$ValueState(const std::string &name, Stack &stack) : State(stack), name_(name) {
        CHANGE_STATE("CreateVariable$ValueState");
    }

    State *parse(const std::string &text, int position) override {

        if (text[position] == ';') {
            Matrix matrix;
            bool succes = Matrix::parse_matrix(buffer, matrix);

            if (succes) {
                stack_.push_back(new Variable(name_, matrix));
                return nullptr;
            }
            return new Error("Bad matrix", stack_);
        }

        if (!Utility::whitespace(text[position])) {
            buffer.push_back(text[position]);
            return this;
        }
        if (Utility::whitespace(text[position]))
            return this;
    }
};


class CreateVariable$NameState : public State {
    std::string buffer;
public:
    CreateVariable$NameState(Stack &stack) : State(stack) {
        CHANGE_STATE("CreateVariable$NameState");
    }

    State *parse(const std::string &text, int position) override {

        if (text[position] == '=')
            return new CreateVariable$ValueState(buffer, stack_);

        if (!Utility::whitespace(text[position])) {
            buffer += text[position];
            return this;
        }

        if (Utility::whitespace(text[position]))
            return this;


        return new Error("Expected =", stack_);
    }
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H
