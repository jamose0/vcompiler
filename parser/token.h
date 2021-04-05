#ifndef TOKEN_H
#define TOKEN_H

#include <string>
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
    RBRACKET,
    LBRACKET,

    /* Operators */
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EQ,
    EQ_EQ,
    GR,
    GR_EQ,
    LE,
    LE_EQ,
    BANG,
    BANG_EQ,

    /* Keywords */
    IF,
    INT,
    FLOAT,
    VAR,

    /* Identifier */
    IDENT,

    /* end */
    END,
    // more to come!
};

class Token {
private:
    TokenType m_type;
    std::string m_lexeme;

public:
    Token(TokenType type, std::string_view lexeme)
        : m_type{type}, m_lexeme{lexeme}
    {
    }

    TokenType getType() const;

    std::string_view getLexeme() const;

    friend std::ostream& operator<<(std::ostream &out, const Token &t);
};

#define MAKE_TOK(type, sp, len) \
    Token{TokenType::type, std::string{sp, len}}

#endif
