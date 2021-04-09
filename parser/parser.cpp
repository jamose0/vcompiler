/* Definitions for Parser class */
#include "parser.h"
#include "parseerror.h"

#include "ast.h"

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
        // Throw a parse error if the next token is not what we expect it
        // to be.
        throw ParseError{"Failed expect"};
    }
}

const Token& Parser::getCurrentTok() const
{
    return m_current_tok;
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
        std::cerr << "Accepted RPAREN\n";
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
        std::cerr << "found star\n";
        advanceToken();
        factor();
        termP();
    } else if (accept(TokenType::SLASH)) {
        std::cerr << "found slash\n";
        advanceToken();
        factor();
        termP();
    }
}

void Parser::exprP()
{
    if (accept(TokenType::PLUS)) {
        std::cerr << "found plus\n";
        advanceToken();
        term();
        exprP();
    } else if (accept(TokenType::MINUS)) {
        std::cerr << "found minus\n";
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
    std::cout << "token at stmt -> " << getCurrentTok() << '\n';
    if (accept(TokenType::MINUS) ||
        accept(TokenType::LPAREN) ||
        accept(TokenType::IDENT) ||
        accept(TokenType::INTEGER_L)) {
        expr();
    } else if (accept(TokenType::VAR)) {
        std::cout << "Found var\n";
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
    Ast a{};
    std::cout << getCurrentTok() << '\n';
    block();
}
