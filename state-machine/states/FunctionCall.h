//
// Created by mateu on 6/4/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTIONCALL_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTIONCALL_H

#include <utility>
#include <Function.h>

#include "Token.h"
#include "State.h"
#include "Scope.h"
#include "Utility.h"

class FunctionCall : public State {
    std::string function_name_;
    std::string buffer_;
public:
    FunctionCall(Stack &stack, std::string buffer) : State(stack), function_name_(std::move(buffer)) {
        stack.push_back(new Scope(function_name_ + "Call"));
    }

    State *parse(const std::string &text, int position) override {

        auto push_value = [this]() {
            Token *token = Utility::find_token(stack_, buffer_);
            if (token) {
                stack_.push_back(token);
                buffer_ = "";
                return (State *) this;
            }

            if (Matrix::is_matrix(buffer_)) {
                Matrix matrix;
                if (Matrix::parse_matrix(buffer_, matrix)) {
                    stack_.push_back(new Variable("arg", matrix));
                    return (State *) this;
                }
            }

            return (State *) new Error("Could not find token", stack_);
        };

        if (text[position] == ',') {
            return push_value();
        }

        if (text[position] == ')') {

            if (!buffer_.empty())
                return push_value();
        }

        if (text[position] == ';'){
            // call the fucntion
            Token *token = Utility::find_token(stack_, function_name_);
            if (token != nullptr) {
                Function *function = (Function *) token;
                auto func = function->get_value();
                func(stack_);
                return nullptr;
            }
            return new Error("Bad function call: \"" + function_name_ + "\"", stack_);
        }


        if (!Utility::whitespace(text[position])) {
            buffer_.push_back(text[position]);
            return this;
        }
    }

    ~FunctionCall() {
//        Token* token = stack_.back();
//        while (token->get_name() != function_name_ + "Call"){
//            stack_.pop_back();
//            token = stack_.back();
//        }
    }
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_FUNCTIONCALL_H
