//
// Created by mateu on 6/3/2021.
//

#include "Matrix.h"

/// \brief State used for creating rows in matrix
class RowState : public State {
    /// \brief Matrix val that is being build
    Matrix &matrix;
    /// \brief Temporary buffer
    std::string buffer;
public:
    RowState(Stack &stack, Matrix &matrix) : State(stack), matrix(matrix) {
        CHANGE_STATE("RowState");
    }

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

/// \brief State used for creating first row in Matrix
class FirstRowState : public State {
    /// \brief Matrix val that is being build
    Matrix &matrix;
    /// \brief if the matrix being parsed is a string literal we need to act differently
    bool is_string;
    /// \brief Temporary buffer
    std::string buffer;
public:
    FirstRowState(Stack &stack, Matrix &matrix) : State(stack), matrix(matrix) {
        is_string = false;
        CHANGE_STATE("FristRowState");
    }

    State *parse(const std::string &text, int position) override {
        if (text[position - 1] == '"') {
            if (!is_string) {
                matrix.add_row();
                matrix.add_column();
                matrix.add_value(text[position]);
                is_string = true;
                return this;
            }
        }

        if (!is_string) {
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
        } else {
            if (text[position] == '"') {
                return nullptr;
            }
            matrix.add_column();
            matrix.add_value(text[position]);
            return this;
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

/// Function that parses a matrix and assigns it into @matrix
/// \param code code to be parsed
/// \param matrix matrix to bullied up
/// \return true if parsing completed successfully and false if it failed
bool Matrix::parse_matrix(const std::string &code, Matrix &matrix) {
    Stack stack;
    if (code == "null") {
        return true;
    }
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

// Thanks to https://github.com/piotr233 for impl
/// Create string representing the matrix
/// \return string representation of the matrix
std::string Matrix::repr() {

    std::string out;
    out += "[";
    for (unsigned i = 0; i < rows; i++) {
        out += "[";
        for (unsigned j = 0; j < cols; j++) {
            out += std::to_string(data_[i * cols + j]);
            if (j != cols - 1)
                out += ", ";
        }
        out += "]";
        if (i != rows - 1) out += "\n";
    }
    out += "]\n";
    return out;
}
