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

/*bool Parser::accept(const TokenType &t)
{
    return t == m_current_tok.getType();
}*/

/*void Parser::expect(const TokenType &t)
{
    std::cout << "current -> " << m_current_tok << '\n';
    if (!accept(t)) {
        // Throw a parse error if the next token is not what we expect it
        // to be.
        throw ParseError{"Failed expect"};
    }
}*/

/*static bool accept(const TokenType &t)
{
    return t == getCurrentTok().getType();
}*/

const Token& Parser::getCurrentTok() const
{
    return m_current_tok;
}

static bool accept(const Parser &p, const TokenType &t)
{
    return t == p.getCurrentTok().getType();
}

void Parser::expect(const TokenType &t)
{
    std::cout << "current -> " << m_current_tok << '\n';
    if (!accept(*this, t)) {
        throw ParseError{"failed expect!"};
    }
}

void Parser::advanceToken()
{
    m_current_tok = m_scanner.nextToken();
}

void Parser::factor()
{
    std::cout << "tok at factor -> " << m_current_tok << '\n';
    if (accept(*this, TokenType::MINUS)) {
        advanceToken();
        factor();
    } else if (accept(*this, TokenType::LPAREN)) {
        advanceToken();
        expr();
        expect(TokenType::RPAREN);
        advanceToken();
    } else if (accept(*this, TokenType::IDENT)) {
        std::cout << "found identifier!\n";
        advanceToken();
    } else if (accept(*this, TokenType::INTEGER_L)) {
        std::cout << "found an integer literal!\n";
        advanceToken();
    } else {
        throw ParseError{"couldn't match at factor"};
    }
}

void Parser::termP()
{
    if (accept(*this, TokenType::STAR)) {
        advanceToken();
        factor();
        termP();
    } else if (accept(*this, TokenType::SLASH)) {
        advanceToken();
        factor();
        termP();
    }
}

void Parser::exprP()
{
    if (accept(*this, TokenType::PLUS)) {
        advanceToken();
        term();
        exprP();
    } else if (accept(*this, TokenType::PLUS)) {
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
    if (accept(*this, TokenType::MINUS) ||
        accept(*this, TokenType::LPAREN) ||
        accept(*this, TokenType::IDENT) ||
        accept(*this, TokenType::INTEGER_L)) {
        expr();
    } else if (accept(*this, TokenType::VAR)) {
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

    if (accept(*this, TokenType::END)) {
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
