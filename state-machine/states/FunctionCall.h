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

/// \brief State used for function calls
class FunctionCall : public State {
    /// \brief return value from called function if function returns nullptr else
    Variable *target_token_;
    /// \brief Name of the function to be called
    std::string function_name_;

    /// \brief used for building up variables to be passed to a function
    std::string buffer_;

    /// \brief Cleans up the stack after exiting functions scope
    void clean() {
        Token *token = stack_.back();
        while (token->get_name() != function_name_ + "Call") {
            stack_.pop_back();
            token = stack_.back();
        }
        stack_.pop_back();
    }

public:
    FunctionCall(Stack &stack, std::string buffer, Token *token) : State(stack),
                                                                   function_name_(std::move(buffer)),
                                                                   target_token_((Variable *) token) {
        CHANGE_STATE("FunctionCall");
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

            if (Matrix::IsMatrix(buffer_)) {
                Matrix matrix;
                if (Matrix::ParseMatrix(buffer_, matrix)) {
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

        if (text[position] == ';') {
            // call the fucntion
            Token *token = Utility::find_token(stack_, function_name_);
            if (token != nullptr) {
                Function *function = (Function *) token;
                auto func = function->get_value();
                int number_of_return_vars = func(stack_);
                if (target_token_) {
                    Variable *result = (Variable *) stack_.back();
                    target_token_->set_value(result->get_value());
                }
                clean();
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
