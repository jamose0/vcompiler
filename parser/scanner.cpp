#include "scanner.h"
#include "token.h"

#include <iostream>

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

Token Scanner::nextToken()
{
    std::cout << "getting next token!\n";

    skipWS();
    if (*m_ip == '#') {
        skipToEndl();
    }
    skipWS();

    std::cout << *m_ip << '\n';
    return Token{TokenType::STRING_L, "next token"};
}
