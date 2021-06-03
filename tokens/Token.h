//
// Created by mateusz on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H

class Token {
public:
    enum TokenType {
        variable,
    };

    virtual const std::string &get_name() = 0;

    virtual TokenType get_type() = 0;
};


#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H
