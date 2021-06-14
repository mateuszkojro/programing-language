//
// Created by mateusz on 6/3/2021.
//

#ifndef UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H
#define UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H

/// \brief Interface for all the Tokens encounter in the code
class Token {
public:

    /// \brief Every token needs to know whats it type is
    enum TokenType {
        variable,
        function,
        scope
    };

    /// Get the name used to access the token in the code
    /// \return name of the tokne in code
    virtual const std::string &get_name() = 0;

    /// Return the type of the token being accessed
    /// \return the type of the token
    virtual TokenType get_type() = 0;
};

using Stack = std::vector<Token *>;

#endif //UI4_PROGRAMOWANIE_OBIEKTOWE_TOKEN_H
