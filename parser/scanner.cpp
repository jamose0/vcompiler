#include "scanner.h"
#include "token.h"

#include <iostream>

#include <cstring>

Scanner::Scanner(std::string_view src)
    : m_src{src}
{
    m_ip = const_cast<char*>(m_src.data());
}

bool Scanner::isWS()
{
    return (*m_ip == ' ' || *m_ip == '\t' || *m_ip == '\n');
}

void Scanner::skipWS()
{
    while (isWS()) {
        ++m_ip;
    }
}

void Scanner::skipToEndl()
{
    while (*(m_ip++) != '\n')
    {
    }
}

bool Scanner::isEligibleForIdent()
{
    return (isalpha(*m_ip) || isdigit(*m_ip) || *m_ip == '_');
}

bool Scanner::matchKW(std::string_view kw, char* sp)
{
    if (strncmp(kw.data(), sp, kw.length()) == 0) {
        m_ip += kw.length() - 1;

        return !isEligibleForIdent();
    }

    return false;
}

Token Scanner::getNumber(char* sp)
{
    while (isdigit(*m_ip)) {
        ++m_ip;

        if (*m_ip == '.') {
            ++m_ip;
            while (isdigit(*m_ip)) {
                ++m_ip;
            }

            return MAKE_TOK(FLOAT_L, sp, static_cast<size_t>(m_ip - sp));
        }
    }
    return MAKE_TOK(INTEGER_L, sp, static_cast<size_t>(m_ip - sp));
}

Token Scanner::getIdent(char* sp)
{
    while (isEligibleForIdent()) {
        ++m_ip;
    }

    return MAKE_TOK(IDENT, sp, static_cast<size_t>(m_ip - sp));
}

Token Scanner::nextToken()
{
    std::cout << "getting next token!\n";

    if (*m_ip == '\0' || *m_ip == EOF) {
        return Token{TokenType::END, "end"};
    }

    skipWS();
    if (*m_ip == '#') {
        skipToEndl();
    }
    skipWS();

    // sp is a pointer to the first character of the next token
    char* sp = (m_ip++);

    switch (*sp) {
        /* --- Keywords --- */
        case 'i':
            std::cout << "matched i\n";
            if (matchKW("int", sp)) {
                std::cout << "matched int\n";
                return MAKE_TOK(INT, sp, 3);
            } else if (matchKW("if", sp)) {
                std::cout << "matched if\n";
                return MAKE_TOK(IF, sp, 2);
            }
            break;
        case 'f':
            std::cout << "matched f\n";
            if (matchKW("float", sp)) {
                std::cout << "matched float\n";
                return MAKE_TOK(FLOAT, sp, 5);
            }
            break;
        case 'v':
            std::cout << "matched v\n";
            if (matchKW("var", sp)) {
                std::cout << "matched var\n";
                return MAKE_TOK(VAR, sp, 3);
            }
            break;
        /* --- Punctuation --- */
        /* --- Operators --- */
        // single character operators
        case '*': return MAKE_TOK(STAR, sp, 1);
        case '/': return MAKE_TOK(SLASH, sp, 1);
        case '-': return MAKE_TOK(MINUS, sp, 1);
        case '+': return MAKE_TOK(PLUS, sp, 1);
        // Operators that may or may not be two character operators
        case '=': {
            if (*(m_ip++) == '=')  {
                return MAKE_TOK(EQ_EQ, sp, 2);
            }
            return MAKE_TOK(EQ, sp, 1);
        }


    }

    m_ip = sp;

    if (isdigit(*m_ip)) {
        return getNumber(sp);
    } else if (isEligibleForIdent()) {
        return getIdent(sp);
    }

    std::cout << *m_ip << '\n';
    return Token{TokenType::STRING_L, "next token"};
}
