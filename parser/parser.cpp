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

// Make the next two functions take a TokenType as first parameter too.
static bool accept(const TokenType &t1, const TokenType &t2)
{
    return t1 == t2;
}

static void expect(const TokenType &p, const TokenType &t)
{
    //std::cout << "current -> " << p.getCurrentTok() << '\n';
    if (!accept(p, t))
        throw ParseError{"failed expect!"};
}

/*void Parser::expect(const TokenType &t)
{
    std::cout << "current -> " << m_current_tok << '\n';
    if (!accept(*this, t)) {
        throw ParseError{"failed expect!"};
    }
}*/

void Parser::advanceToken()
{
    m_current_tok = m_scanner.nextToken();
}

void Parser::factor()
{
    std::cout << "tok at factor -> " << m_current_tok << '\n';
    if (accept(m_current_tok.getType(), TokenType::MINUS)) {
        advanceToken();
        factor();
    } else if (accept(m_current_tok.getType(), TokenType::LPAREN)) {
        advanceToken();
        expr();
        expect(m_current_tok.getType(), TokenType::RPAREN);
        std::cerr << "Accepted RPAREN\n";
        advanceToken();
    } else if (accept(m_current_tok.getType(), TokenType::IDENT)) {
        std::cout << "found identifier!\n";
        advanceToken();
    } else if (accept(m_current_tok.getType(), TokenType::INTEGER_L)) {
        std::cout << "found an integer literal!\n";
        advanceToken();
    } else {
        throw ParseError{"couldn't match at factor"};
    }
}

void Parser::termP()
{
    if (accept(m_current_tok.getType(), TokenType::STAR)) {
        std::cerr << "found star\n";
        advanceToken();
        factor();
        termP();
    } else if (accept(m_current_tok.getType(), TokenType::SLASH)) {
        std::cerr << "found slash\n";
        advanceToken();
        factor();
        termP();
    }
}

void Parser::exprP()
{
    if (accept(m_current_tok.getType(), TokenType::PLUS)) {
        std::cerr << "found plus\n";
        advanceToken();
        term();
        exprP();
    } else if (accept(m_current_tok.getType(), TokenType::MINUS)) {
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
    if (accept(m_current_tok.getType(), TokenType::MINUS) ||
        accept(m_current_tok.getType(), TokenType::LPAREN) ||
        accept(m_current_tok.getType(), TokenType::IDENT) ||
        accept(m_current_tok.getType(), TokenType::INTEGER_L)) {
        expr();
    } else if (accept(m_current_tok.getType(), TokenType::VAR)) {
        std::cout << "Found var\n";
        advanceToken();
        expect(m_current_tok.getType(), TokenType::IDENT);
        advanceToken();
        expect(m_current_tok.getType(), TokenType::EQ);
        std::cout << "calling expr\n";
        advanceToken();
        expr();
        expect(m_current_tok.getType(), TokenType::SEMICOLON);
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

    if (accept(m_current_tok.getType(), TokenType::END)) {
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
