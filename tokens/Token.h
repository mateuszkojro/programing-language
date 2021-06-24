//
// Created by mateusz on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H

#include <string>
/// \brief Interface for all the Tokens encounter in the code
class Token {
public:

    /// \brief Every token needs to know whats it type is
    enum TokenType {
        VARIABLE,
        FUNCTION,
        SCOPE
    };

    /// Get the name used to access the token in the code
    /// \return name of the tokne in code
    virtual const std::string &GetName() = 0;

    /// Return the type of the token being accessed
    /// \return the type of the token
    virtual TokenType GetType() = 0;
};

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H
