#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

#include <string_view>

class Scanner {
private:
    std::string_view m_src;
    char* m_ip;

    /* Returns true if m_ip points to ' ', '\t', or '\n' */
    bool isWS();

    /* Moves m_ip to the first non-whitespace character */
    void skipWS();

    void skipToEndl();

    bool isEligibleForIdent();

    bool matchKW(std::string_view kw, char* sp);

    Token getNumber(char* sp);

public:
    Scanner(std::string_view src);

    Token nextToken();
};

#endif
