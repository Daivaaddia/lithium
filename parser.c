#include <stdio.h>
#include <stdlib.h>

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

static struct astNode *operandNode(struct token tok) {
    struct astNode *n;
    switch(tok.token) {
        case T_INTLIT:
            n = createNode(tokenToNodeType(tok.token), NULL, NULL, tok.value);
            return n;
        default:
            fprintf(stderr, "Something went wrong in operandNode()\n");
            exit(1);
    }
}

static struct astNode *multExpr(FILE *file, struct token *tok) {
    scan(file, tok);

    struct astNode *left = operandNode(*tok);

    scan(file, tok);
    if (tok->token == T_EOF) {
        return left;
    } 

    while(tok->token == T_STAR || tok->token == T_LSLASH) {
        TokenType opTokenType = tok->token;
        // INTLIT expected
        scan(file, tok);
        struct astNode *right = operandNode(*tok);

        left = createNode(tokenToNodeType(opTokenType), left, right, 0);

        scan(file, tok);
        if (tok->token == T_EOF) {
            break;
        }
    }

    return left;
}

static struct astNode *addExpr(FILE *file) {
    struct token tok;
    struct astNode *left = multExpr(file, &tok);

    if (tok.token == T_EOF) {
        return left;
    }

    while(1) {
        TokenType opTokenType = tok.token;
        // scan for next expression
        struct astNode *right = multExpr(file, &tok);

        left = createNode(tokenToNodeType(opTokenType), left, right, 0);

        if (tok.token == T_EOF) {
            break;
        }
    }

    return left;
}

struct astNode *parse(FILE *file) {
    return addExpr(file);
}
