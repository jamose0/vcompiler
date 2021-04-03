#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

#include <string_view>

class Scanner {
private:
    std::string_view m_src;
    char* m_ip;

public:
    Scanner(std::string_view src);

    Token nextToken();
};

#endif
