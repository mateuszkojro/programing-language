//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H

#include "Base.h"
#include "FunctionCall.h"

/// \brief State used for parsing variables
class VariableAssigment : public State {
    /// \brief Buffer containing the code for the variable value (it will be parsed latter)
    std::string value_buffer;
    /// \brief Variable that is being built up
    Variable *variable_;
public:
    VariableAssigment(Stack &stack, Variable *variable) : State(stack), variable_(variable) {
        CHANGE_STATE("VariableAssigment");
    }

//    static bool parse_variable(const std::string &code, Variable **variable) {
//        Stack stack;
//        State* current_state = new VariableAssigment(stack, *variable);
//        for (int i = 1; i < code.size(); i++) {
//            State *next_state = current_state->parse(code, i);
//            if (next_state == nullptr)
//                return true;
//            if (current_state != next_state) {
//                delete current_state;
//                current_state = next_state;
//            }
//        }
//        return false;
//    }

    State *parse(const std::string &text, int position) override {
        if (Utility::whitespace(text[position])) {
            return this;
        }
        if (text[position] == '=') {
            return this;
        }
        if (text[position] == '(') {
            return new FunctionCall(stack_, value_buffer, variable_);
        }
        if (text[position] == ';') {
            if (Matrix::is_matrix(value_buffer)) {
                Matrix matrix;
                if (Matrix::parse_matrix(value_buffer, matrix)) {
                    variable_->set_value(matrix);
                    return nullptr;
                }
                return new Error("Bad matrix", stack_);
            }
            Token *token = Utility::find_token(stack_, value_buffer);
            if (token) {
                Variable *temp = (Variable *) token;
                variable_->set_value(temp->get_value());
                return nullptr;
            }
            return new Error("Expected new matrix or variable name ", stack_);
        }
        if (!Utility::whitespace(text[position])) {
            value_buffer.push_back(text[position]);
            return this;
        }
    }
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H
