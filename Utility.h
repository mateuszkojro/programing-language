//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_UTILITY_H

class Utility {
public:
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
