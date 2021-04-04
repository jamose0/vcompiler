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
        m_ip += kw.length();

        return !isEligibleForIdent();
    }

    return false;
}

Token Scanner::nextToken()
{
    std::cout << "getting next token!\n";

    skipWS();
    if (*m_ip == '#') {
        skipToEndl();
    }
    skipWS();

    // sp is a pointer to the first character of the next token
    char* sp = m_ip;

    switch (*sp) {
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
    }

    std::cout << *m_ip << '\n';
    return Token{TokenType::STRING_L, "next token"};
}
