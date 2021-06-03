//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_VARIABLEASSIGMENT_H

class VariableAssigment : public State {
    std::string value_buffer;
    Variable *variable_;
public:
    VariableAssigment(Stack &stack, Variable *variable) : State(stack), variable_(variable) {}

    State *parse(const std::string &text, int position) override {
        if (Utility::whitespace(text[position])) {
            return this;
        }
        if (text[position] == '=') {
            return this;
        }
        if (text[position] == ';') {
            if (Matrix::is_matrix(value_buffer)) {
                Matrix matrix;
                if (Matrix::parse_matrix(value_buffer, matrix)) {
                    variable_->set_value(matrix);
                    return new Error("Assigment succesfull", stack_);
                }
                return new Error("Bad matrix", stack_);
            }
            Token *token = Utility::find_token(stack_, value_buffer);
            if (token) {
                Variable *temp = (Variable *) token;
                variable_->set_value(temp->get_value());
                return new Error("Assigment succesfull", stack_);
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
