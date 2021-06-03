//
// Created by mateu on 6/3/2021.
//

#include "Matrix.h"

class RowState : public State {
    Matrix &matrix;
    std::string buffer;
public:
    RowState(Stack &stack, Matrix &matrix) : State(stack), matrix(matrix) {}

    State *parse(const std::string &text, int position) override {
        if (text[position] == '[')
            return this;

        if (text[position] == ',') {
            matrix.add_value(std::stod(buffer));
            buffer = "";
            return this;
        }
        if (text[position] == ']') {
            matrix.add_value(std::stod(buffer));
            buffer = "";
            if (text[position + 1] == ']')
                return nullptr;
            matrix.add_row();
            return new RowState(stack_, matrix);
        }
        if (!Utility::whitespace(text[position])) {
            buffer.push_back(text[position]);
            return this;
        }
        if (Utility::whitespace(text[position])) {
            return this;
        }
    }

};

class FirstRowState : public State {
    Matrix &matrix;
    std::string buffer;
public:
    FirstRowState(Stack &stack, Matrix &matrix) : State(stack), matrix(matrix) {}

    State *parse(const std::string &text, int position) override {
        if (text[position] == '[') {
            matrix.add_row();
            return this;
        }
        if (text[position] == ',') {
            matrix.add_column();
            matrix.add_value(std::stod(buffer));
            buffer = "";
            return this;
        }
        if (text[position] == ']') {
            matrix.add_column();
            matrix.add_value(std::stod(buffer));
            buffer = "";
            if (text[position + 1] == ']')
                return nullptr;

            matrix.add_row();
            return new RowState(stack_, matrix);
        }
        if (!Utility::whitespace(text[position])) {
            buffer.push_back(text[position]);
            return this;
        }
        if (Utility::whitespace(text[position])) {
            return this;
        }

    }
};


bool Matrix::parse_matrix(const std::string &code, Matrix &matrix) {
    Stack stack;
    State *cureent_state = new FirstRowState(stack, matrix);
    for (int i = 1; i < code.size(); i++) {
        State *next_state = cureent_state->parse(code, i);
        if (next_state == nullptr)
            return true;
        if (cureent_state != next_state) {
            delete cureent_state;
            cureent_state = next_state;
        }
    }
    return false;
}