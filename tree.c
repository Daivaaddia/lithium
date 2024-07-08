#include <stdlib.h>
#include <stdio.h>

#include "defs.h"

struct astNode *createNode(ASTNodeType type, struct astNode *left, struct astNode *right, int val) {
    struct astNode *new = malloc(sizeof(*new));
    if (new == NULL) {
        fprintf(stderr, "Unable to allocate new tree node");
        exit(1);
    }

    new->type = type;
    new->left = left;
    new->right = right;
    new->val = val;
    return new;
}