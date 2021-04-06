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

#endif
