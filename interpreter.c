#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

static char *opStrings[] = { "+", "-", "*", "/" };

int interpret(struct astNode *node) {
    int leftVal;
    int rightVal;
    if (node->left) {
        leftVal = interpret(node->left);
    }
    if (node->right) {
        rightVal = interpret(node->right);
    }

    if (node->type == A_INTLIT) {
        printf("val %d\n", node->val);
    } else {
        printf("%d %s %d\n", leftVal, opStrings[node->type], rightVal);
    }

    switch(node->type) {
        case A_ADD:
            return leftVal + rightVal;
        case A_SUB:
            return leftVal - rightVal;
        case A_MUL: 
            return leftVal * rightVal;
        case A_DIV:
            return leftVal / rightVal;
        case A_INTLIT:
            return node->val;
        default:
            fprintf(stderr, "Unknown node type in interpret()\n");
            exit(1);
    }
}