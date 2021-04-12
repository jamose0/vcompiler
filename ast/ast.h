#ifndef AST_H
#define AST_H

#include "astnode.h"

#include <iostream>
#include <memory>

class Ast {
private:
    std::unique_ptr<AstNode> root;

public:
    Ast()
    {
        std::cout << "hello, world!\n";
    }
};

#endif
