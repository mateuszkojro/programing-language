//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H

#include "../State.h"
#include "Base.h"
#include "Error.h"
#include "VariableAssigment.h"

class CreateVariableValueState : public State {
    std::string name_;
    std::string buffer_;
public:
    CreateVariableValueState(std::string name, Stack &stack);

    State *Parse(const std::string &text, int position) override;
};


class CreateVariableNameState : public State {
    std::string buffer_;
public:
    explicit CreateVariableNameState(Stack &stack);

    State *Parse(const std::string &text, int position) override;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H
