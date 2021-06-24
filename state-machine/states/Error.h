//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_ERROR_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_ERROR_H

class Error : public State {
public:
    explicit Error(const std::string &error, Stack &stack);

    State *Parse(const std::string &text, int position) override;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_ERROR_H
