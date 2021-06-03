#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include <string>
#include "tokens/Variable.h"


class Parser;

class Error : public State {
public:
    explicit Error(const std::string &error, Stack &stack) : State(stack) {
        std::cout << error << std::endl;
        exit(1);
    }

    State *parse(const std::string &text, int position) override {
        return nullptr;
    }
};

class Base;

bool is_number(char znak) {
    if (znak >= 30 && znak <= 39)
        return true;
    return false;
}

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



        // todo there should be whole matrix parser here
        if (text[position] == '[') {
            if (open_matrix == 0) {
                open_matrix += 1;
                return this;
            } else {
                assert(open_matrix < 3);
                if (open_matrix % 2 == 1)
                    value.add_row();
                else
                    value.add_column();
                open_matrix += 1;
            }
        }

        // todo There should be whole number pasing thing
        if (is_number(text[position])) {
            std::string temp = reinterpret_cast<const char *const>(text[position]);
            value.add_value(std::stoi(temp));
        }

        if (text[position] == ']') {
            if (open_matrix == 0) {
                ready = true;
            } else {
                open_matrix -= 1;
            }
        }


        if (ready) {
            stack_.push_back(new Variable(name_, value));
            return new Error("OK", stack_);
        }
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

Token *find_token(const Stack &stack, const std::string &token_name) {
    for (Token *token: stack) {
        if (token->get_name() == token_name)
            return token;
    }
    return nullptr;
}

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
            Token *token = find_token(stack_, value_buffer);
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

class Base : public State {
    std::string buffer;
public:
    Base(Stack &stack) : State(stack) {
        buffer = "";
    }

    State *parse(const std::string &text, int position) override {
        if (!Utility::whitespace(text[position])) {
            std::cout << text[position];
            buffer.push_back(text[position]);
            return this;
        }

        if (buffer == "mat") {
            return new CreateVariable$NameState(stack_);
        }

        Token *token = find_token(stack_, buffer);
        if (token) {
            return new VariableAssigment(stack_, (Variable *) token);
        }

        std::cout << "buffer: " << buffer << "\n";
        return new Error("Token not found: " + buffer, stack_);
    }

};


class Parser {
public:
    Stack stack_;

    void parse_string(const std::string &code) {
        current_state_ = new Base(stack_);
        for (int i = 0; i < code.size(); i++) {
            State *next_state = current_state_->parse(code, i);
            if (next_state != current_state_) {
                delete current_state_;
                current_state_ = next_state;
            }
            // skip whitespace
        }
    }

private:
    State *current_state_;
};

int main() {
    Parser parser;
    Matrix matrix;
    Matrix::parse_matrix("[[1]]", matrix);
    parser.stack_.push_back(new Variable("x", matrix));
    parser.parse_string("x = [[1,2,3]];");
    return 0;
}
