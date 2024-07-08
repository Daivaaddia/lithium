#include <stdio.h>

#include "defs.h"

ASTNodeType tokenToNodeType(TokenType tok) {
    switch (tok) {
        case T_PLUS:
            return A_ADD;
        case T_MINUS:
            return A_SUB;
        case T_STAR:
            return A_MUL;
        case T_LSLASH: 
            return A_DIV;
        case T_INTLIT:
            return A_INTLIT;
        default:
            fprintf(stderr, "Unknown token input to tokenToNodeType()");
            exit(1);
    }
}

