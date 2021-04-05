#include "token.h"

#include <iostream>

TokenType Token::getType() const
{
    return m_type;
}

std::string_view Token::getLexeme() const
{
    return m_lexeme;
}

std::ostream& operator<<(std::ostream &out, const Token &t)
{
    out << "TOKEN: TYPE -> ";
    switch (t.m_type) {
        case TokenType::INTEGER_L:
            out << "INTEGER_L";
            break;
        case TokenType::STRING_L:
            out << "STRING_L";
            break;
        case TokenType::FLOAT_L:
            out << "FLOAT_L";
            break;
        case TokenType::SEMICOLON:
            out << "SEMICOLON";
            break;
        case TokenType::RBRACE:
            out << "RBRACE";
            break;
        case TokenType::LBRACE:
            out << "LBRACE";
            break;
        case TokenType::RPAREN:
            out << "RPAREN";
            break;
        case TokenType::LPAREN:
            out << "LPAREN";
            break;
        case TokenType::PLUS:
            out << "PLUS";
            break;
        case TokenType::MINUS:
            out << "MINUS";
            break;
        case TokenType::STAR:
            out << "STAR";
            break;
        case TokenType::SLASH:
            out << "SLASH";
            break;
        case TokenType::EQ:
            out << "EQ";
            break;
        case TokenType::EQ_EQ:
            out << "EQ_EQ";
            break;
        case TokenType::GR:
            out << "GR";
            break;
        case TokenType::GR_EQ:
            out << "GR_EQ";
            break;
        case TokenType::LE:
            out << "LE";
            break;
        case TokenType::LE_EQ:
            out << "LE_EQ";
            break;
        case TokenType::BANG:
            out << "BANG";
            break;
        case TokenType::BANG_EQ:
            out << "BANG_EQ";
            break;
        case TokenType::IF:
            out << "IF";
            break;
        case TokenType::INT:
            out << "INT";
            break;
        case TokenType::FLOAT:
            out << "FLOAT";
            break;
        case TokenType::VAR:
            out << "VAR";
            break;
        case TokenType::IDENT:
            out << "IDENT";
            break;
        case TokenType::END:
            out << "END";
            break;
        default:
            out << "No match";
            break;
    }
    out << " | LEXEME -> " << t.m_lexeme;

    return out;
}
