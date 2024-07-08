// TOKENS

typedef enum TokenType {
    T_SEMI, T_PLUS, T_MINUS, T_STAR, T_LSLASH, T_INTLIT, T_EXIT
} TokenType;

struct token {
    TokenType token;
    int value;
};

// AST

typedef enum ASTNodeType {
    A_ADD, A_SUB, A_MUL, A_DIV, A_INTLIT
} ASTNodeType;

struct astNode {
    ASTNodeType type;
    struct astNode *left;
    struct astNode *right;
    int val;                // only for A_INTLIT
};