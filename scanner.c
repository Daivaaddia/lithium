#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "defs.h"
#include "scanner.h"


static int scanInt(FILE *file) {
    // initial fgetc must be a digit
    int num = 0;
    int byte;
    while ((byte = fgetc(file)) != EOF && isdigit(byte)) {      
        num *= 10;
        num += byte - '0';
    }
    if (byte != EOF) {
        fseek(file, -1, SEEK_CUR);
    }
    
    return num;
}

int scan(FILE *file, struct token *tok) {
    int byte = fgetc(file);
    // skip whitespace
    while (isspace(byte)) {
        byte = fgetc(file);
        if (byte == EOF) {
            return 0;
        }
    }

    switch(byte) {
        case EOF:
            return 0;
        case '+':
            tok->token = T_PLUS;
            break;
        case '-':
            tok->token = T_MINUS;
            break;
        case '*':
            tok->token = T_STAR;
            break;
        case '/':
            tok->token = T_LSLASH;
            break;
        case ';':
            tok->token = T_SEMI;
            break;
        default: 
            if (isdigit(byte)) {
                fseek(file, -1, SEEK_CUR);
                tok->token = T_INTLIT;
                tok->value = scanInt(file);
                break;
            } else if (isalpha(byte)) {
                char buf[255] = {};
                buf[0] = byte;
                int index = 1;
                while ((byte = fgetc(file)) != EOF && isalpha(byte)) {
                    buf[index] = byte;
                    index++;
                    if (index == 255) {
                        fprintf(stderr, "String of alphabet too big!");
                        exit(1);
                    }
                }
                if (strcmp(buf, "exit") == 0) {
                    tok->token = T_EXIT;
                    fseek(file, -1, SEEK_CUR);
                    break;
                }
                
                fprintf(stderr, "Invalid syntax found: '%s'\n", buf);
                exit(1);                
            } else {
                fprintf(stderr, "Invalid syntax found: '%c'\n", byte);
                exit(1); 
            }
    }

    return 1;
}