#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "token.h"

#include <string_view>

class Parser {
private:
    Scanner m_scanner;
    Token m_current_tok;

    void advanceToken();

    //bool accept(const TokenType &t);

    void expect(const TokenType &t);

    void factor();

    void termP();

    void exprP();

    void term();

    void expr();

    void stmt();

    void decl();

    void block();

public:
    Parser(std::string_view m_source);

    void parse();

    const Token& getCurrentTok() const;
};

#endif
