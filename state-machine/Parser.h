//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_PARSER_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_PARSER_H

#include "states/Base.h"

class Parser {
public:
    Stack stack_;
    Parser(){
        current_state_ = new Base(stack_);
    }
    void parse_string(const std::string &code) {
//        current_state_ = new Base(stack_);
        for (int i = 0; i < code.size(); i++) {
            std::clog << code[i] << std::endl;
            State *next_state = current_state_->parse(code, i);
            if (next_state == nullptr){
                next_state = new Base(stack_);
                delete current_state_;
                current_state_ = next_state;
            } else if (next_state != current_state_) {
                delete current_state_;
                current_state_ = next_state;
            }
            // skip whitespace
        }
    }

private:
    State *current_state_;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_PARSER_H


/// Notes:
// -