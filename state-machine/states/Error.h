//
// Created by mateu on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_ERROR_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_ERROR_H

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

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_ERROR_H
