#ifndef ASTNODE_H
#define ASTNODE_H

#include "nodetype.h"

class AstNode {
private:

public:
    AstNode();

    virtual NodeType type() const = 0;

    virtual ~AstNode();
};

class UnaryExpr : public AstNode {
private:
    NodeType m_type;

public:
    UnaryExpr()
        : m_type{NodeType::EXPR_UNR}
    {
    }


};

#endif
