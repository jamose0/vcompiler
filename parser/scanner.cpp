#include "scanner.h"
#include "token.h"

#include <iostream>

Scanner::Scanner(std::string_view src)
    : m_src{src}
{
    m_ip = const_cast<char*>(m_src.data());
}

Token Scanner::nextToken()
{
    std::cout << "getting next token!\n";
    return Token{TokenType::STRING_L, "next token"};
}
