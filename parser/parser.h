#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "token.h"

#include <string_view>

class Parser {
private:
    Scanner m_scanner;
    Token m_current_tok;

public:
    Parser(std::string_view m_source);
};

#endif
