#include "parser.h"
#include "parseerror.h"

#include <string_view>
#include <iostream>

Parser::Parser(std::string_view m_source)
    : m_scanner{Scanner{m_source}}, m_current_tok{m_scanner.nextToken()}
{
}

bool Parser::accept(const TokenType &t)
{
    return t == m_current_tok.getType();
}

void Parser::expect(const TokenType &t)
{
    std::cout << "current -> " << m_current_tok << '\n';
    if (!accept(t)) {
        throw ParseError{"Failed expect"};
    }
}

void Parser::advanceToken()
{
    m_current_tok = m_scanner.nextToken();
}

void Parser::factor()
{
    std::cout << "tok at factor -> " << m_current_tok << '\n';
    if (accept(TokenType::MINUS)) {
        advanceToken();
        factor();
    } else if (accept(TokenType::LPAREN)) {
        advanceToken();
        expr();
        expect(TokenType::RPAREN);
        advanceToken();
    } else if (accept(TokenType::IDENT)) {
        std::cout << "found identifier!\n";
        advanceToken();
    } else if (accept(TokenType::INTEGER_L)) {
        std::cout << "found an integer literal!\n";
        advanceToken();
    } else {
        throw ParseError{"couldn't match at factor"};
    }
}

void Parser::termP()
{
    if (accept(TokenType::STAR)) {
        advanceToken();
        factor();
        termP();
    } else if (accept(TokenType::SLASH)) {
        advanceToken();
        factor();
        termP();
    }
}

void Parser::exprP()
{
    if (accept(TokenType::PLUS)) {
        advanceToken();
        term();
        exprP();
    } else if (accept(TokenType::PLUS)) {
        advanceToken();
        term();
        exprP();
    }

}

void Parser::term()
{
    factor();
    termP();
}

void Parser::expr()
{
    term();
    exprP();
}

void Parser::stmt()
{
    if (accept(TokenType::MINUS) ||
        accept(TokenType::LPAREN) ||
        accept(TokenType::IDENT) ||
        accept(TokenType::INTEGER_L)) {
        expr();
    } else if (accept(TokenType::VAR)) {
        advanceToken();
        expect(TokenType::IDENT);
        advanceToken();
        expect(TokenType::EQ);
        std::cout << "calling expr\n";
        advanceToken();
        expr();
        expect(TokenType::SEMICOLON);
        advanceToken();
    }
}

void Parser::decl()
{
    stmt();
}

void Parser::block()
{
    decl();
    std::cout << "token at block -> " << m_current_tok << '\n';

    if (accept(TokenType::END)) {
        std::cout << "we're at the end!\n";
        return;
    }

    block();
}

void Parser::parse()
{
    block();
}
