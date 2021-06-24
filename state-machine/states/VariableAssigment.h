//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H

#include <Variable.h>
#include "Base.h"
#include "FunctionCall.h"

/// \brief State used for parsing variables
class VariableAssigment : public State {
    /// \brief Buffer containing the code for the VARIABLE value (it will be parsed latter)
    std::string value_buffer_;
    /// \brief Variable that is being built up
    Variable *variable_;
public:
    VariableAssigment(Stack &stack, Variable *variable);

//    static bool parse_variable(const std::string &code, Variable **VARIABLE) {
//        Stack stack;
//        State* current_state = new VariableAssigment(stack, *VARIABLE);
//        for (int i = 1; i < code.Size(); i++) {
//            State *next_state = current_state->Parse(code, i);
//            if (next_state == nullptr)
//                return true;
//            if (current_state != next_state) {
//                delete current_state;
//                current_state = next_state;
//            }
//        }
//        return false;
//    }

    State *Parse(const std::string &text, int position) override;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H
