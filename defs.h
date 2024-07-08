// TOKENS

typedef enum TokenType {
    T_SEMI, T_PLUS, T_MINUS, T_STAR, T_LSLASH, T_INTLIT, T_EXIT, T_EOF
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


void scan(FILE *file, struct token *tok);

ASTNodeType tokenToNodeType(TokenType tok);

struct astNode *parse(FILE *file);
struct astNode *createNode(ASTNodeType type, struct astNode *left, struct astNode *right, int val);

int interpret(struct astNode *node);