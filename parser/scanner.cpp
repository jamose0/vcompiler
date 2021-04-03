#include "scanner.h"

#include <iostream>

Scanner::Scanner(std::string_view src)
    : m_src{src}
{
    m_ip = const_cast<char*>(m_src.data());
}
