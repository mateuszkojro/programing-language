//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H

class Utility {
public:
    static Token *find_token(const Stack &stack, const std::string &token_name) {
        for (Token *token: stack) {
            if (token->get_name() == token_name)
                return token;
        }
        return nullptr;
    }

    static bool whitespace(char letter) {
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
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H
