//
// Created by mateu on 6/5/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_CONDITIONAL_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_CONDITIONAL_H

#include <Token.h>
#include "State.h"
#include "Variable.h"
#include "VariableAssigment.h"
#include "../Matrix.h"
#include "../Utility.h"

class Conditional : public State {

    VariableAssigment *condition_parser_;
    Variable *condition_;


public:

    Conditional(Stack &stack) : State(stack) {
        CHANGE_STATE("Conditional");
        Matrix m;
        condition_ = new Variable("if", m);
        condition_parser_ = new VariableAssigment(stack, condition_);
    }

    State *parse(const std::string &text, int position) override {

        if (text[position] == '{') {
            condition_parser_->parse(";", 0);
            delete condition_parser_;
            condition_parser_ = nullptr;
            if (condition_->get_value() == Matrix(true))
                return nullptr;
            return this;
        }

        if (text[position] == '}')
            return nullptr;

        if (condition_parser_) {
            condition_parser_->parse(text, position);
            return this;
        }

        if (Utility::whitespace(text[position])) {
            return this;
        }

        return this;
    }

};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_CONDITIONAL_H
