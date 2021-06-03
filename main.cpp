#include <iostream>
#include <utility>
#include <stack>
#include <vector>
#include <cassert>
#include <string>


class Matrix {
public:

    void add_column() {
        assert(rows == 0);
        cols += 1;
    }

    void add_row() {
        assert(streak == cols);
        rows += 1;
    }

    bool add_value(double value) {
        if (streak > cols)
            return false;
        data_.push_back(value);
        return true;
    }

    Matrix() : cols(0), rows(0) {}

private:
    int streak;
    int cols;
    int rows;
    std::vector<double> data_;
};


using ValueType = Matrix;

class Token {
public:
    enum TokenType {
        variable,
    };

    virtual const std::string &get_name() = 0;

    virtual TokenType get_type() = 0;
};

class Variable : public Token {
public:
    Variable(std::string name, ValueType value)
            : name_(std::move(name)) {}

    std::string &get_name() override {
        return name_;
    }

    TokenType get_type() override {
        return TokenType::variable;
    }

private:
    std::string name_;
};


class Parser;

using Stack = std::stack<Token *>;

class State {
public:
    State(Stack &stack) : stack_(stack) {}

    virtual State *parse(const std::string &text, int position) = 0;

protected:
    Stack &stack_;
};

bool whitespace(char letter) {
    switch (letter) {
        case '\n':
        case '\t':
        case '\r':
        case ' ':
            return true;
        default:
            return false;
    }
}

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


class VariableValueState : public State {
    std::string name_;
    std::string buffer;
    int open_matrix;
    bool ready;
    Matrix value;
public:
    VariableValueState(const std::string &name, Stack &stack) : State(stack), name_(name), open_matrix(0) {
        std::cout << "variable value";
    }

    State *parse(const std::string &text, int position) override {

        std::cout << text[position] << " buffer: " << buffer << std::endl;
        if (text[position] == ';'){
            if (buffer == "null") {
                stack_.push(new Variable(name_, Matrix{}));
                return new Error("NULL", stack_);
            }
        }

        if (!whitespace(text[position])) {
            buffer.push_back(text[position]);
            return this;
        }
        if (whitespace(text[position]))
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
            stack_.push(new Variable(name_, value));
            return new Error("OK", stack_);
        }
    }
};


class VariableNameState : public State {
    std::string buffer;
public:
    VariableNameState(Stack &stack) : State(stack) {
        std::cout << "\nvariable name\n";
    }

    State *parse(const std::string &text, int position) override {
        std::cout << text[position];

        if (text[position] == '=')
            return new VariableValueState(buffer, stack_);

        if (!whitespace(text[position])) {
            buffer += text[position];
            return this;
        }

        if (whitespace(text[position]))
            return this;


        return new Error("Expected =", stack_);
    }
};

class Base : public State {
    std::string buffer;
public:
    Base(Stack &stack) : State(stack) {
        buffer = "";
    }

    State *parse(const std::string &text, int position) override {
        if (!whitespace(text[position])) {
            std::cout << text[position];
            buffer.push_back(text[position]);
            return this;
        }

        if (buffer == "mat") {
            return new VariableNameState(stack_);
        }

        std::cout << "buffer: " << buffer << "\n";
        return new Error("Expected token", stack_);
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

    parser.parse_string("mat x = null;");
    return 0;
}
