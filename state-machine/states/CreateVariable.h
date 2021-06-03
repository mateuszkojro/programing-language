//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_CREATEVARIABLE_H

#include "Error.h"

class CreateVariable$ValueState : public State {
    std::string name_;
    std::string buffer;
    int open_matrix;
    bool ready;
    Matrix value;
public:
    CreateVariable$ValueState(const std::string &name, Stack &stack) : State(stack), name_(name), open_matrix(0) {
        std::cout << "variable value";
    }

    State *parse(const std::string &text, int position) override {

        std::cout << text[position] << " buffer: " << buffer << std::endl;
        if (text[position] == ';') {
            if (buffer == "null") {
                stack_.push_back(new Variable(name_, Matrix{}));
                return new Error("NULL", stack_);
            }

            Matrix matrix;
            bool succes = Matrix::parse_matrix(buffer, matrix);

            if (succes) {
                stack_.push_back(new Variable(name_, matrix));
                return new Error("Good matrix", stack_);
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
        std::cout << "\nvariable name\n";
    }

    State *parse(const std::string &text, int position) override {
        std::cout << text[position];

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
