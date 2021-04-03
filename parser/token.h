#ifndef TOKEN_H
#define TOKEN_H

#include <string_view>

enum class TokenType {
    /* Literals */
    INTEGER_L,
    STRING_L,
    FLOAT_L,

    /* Punct */
    SEMICOLON,
    RBRACE,
    LBRACE,
    RPAREN,
    LPAREN,

    /* Operators */
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EQ,

    /* Keywords */
    IF,
    INT,
    FLOAT,
    VAR,
    // more to come!
};

class Token {
private:
    TokenType m_type;
    std::string_view m_lexeme;

public:
    Token(TokenType type, std::string_view lexeme)
        : m_type{type}, m_lexeme{lexeme}
    {
    }

    friend std::ostream& operator<<(std::ostream &out, const Token &t);
};

#endif
