#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "defs.h"
#include "scanner.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./lithium <file.li>\n");
        exit(1);
    }

    FILE *inpFile = fopen(argv[1], "r");

    if (inpFile == NULL) {
        fprintf(stderr, "Unable to open file %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    char *tokenStrings[7] = {";", "+", "-", "*", "/", "INTLIT", "EXIT"};

    struct token tok;
    while (scan(inpFile, &tok)) {
        printf("Token found: %s", tokenStrings[tok.token]);
        if (tok.token == T_INTLIT) {
            printf(", Value: %d", tok.value);
        }
        putchar('\n');
    }
}