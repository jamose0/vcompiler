#ifndef NODETYPE_H
#define NODETYPE_H

#include <iostream>

enum class NodeType {
    EXPR_BIN,
    EXPR_UNR,
    DECL,
    STATEMENT,
    BLOCK,
    PROGRAM,
};

#endif
