#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define keywords for C language
const char *keywords[] = {
    "int", "float", "char", "if", "else", "for", "while", "return", "void", "double", "do", "break"
};
const int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

// Symbol table to store identifiers
char symbolTable[100][50];
int symbolCount = 0;

// Function to check if a string is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a delimiter
int isDelimiter(char ch) {
    return (ch == ' ' || ch == ',' || ch == ';' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '\n');
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
            ch == '<' || ch == '>' || ch == '%');
}

// Function to add an identifier to the symbol table
void addToSymbolTable(const char *identifier) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i], identifier) == 0) {
            return; // Avoid duplicates
        }
    }
    strcpy(symbolTable[symbolCount++], identifier);
}

// Function to classify tokens and report lexical errors
void classifyToken(const char *token) {
    if (isKeyword(token)) {
        printf("Keyword: %s\n", token);
    } else if (isdigit(token[0])) {
        int validConstant = 1;
        for (int i = 1; token[i] != '\0'; i++) {
            if (!isdigit(token[i])) {
                validConstant = 0;
                break;
            }
        }
        if (validConstant) {
            printf("Constant: %s\n", token);
        } else {
            printf("LEXICAL ERROR: %s invalid lexeme\n", token);
        }
    } else if (token[0] == '\'' || token[0] == '"') {
        printf("String: %s\n", token);
    } else if (isalpha(token[0]) || token[0] == '_') {
        printf("Identifier: %s\n", token);
        addToSymbolTable(token);
    } else {
        printf("LEXICAL ERROR: %s invalid lexeme\n", token);
    }
}

// Main lexical analyzer function
void lexicalAnalyzer(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }

    char ch, buffer[256];
    int index = 0;
    int inComment = 0;

    printf("TOKENS\n");
    while ((ch = fgetc(file)) != EOF) {
        if (!inComment && ch == '/' && (ch = fgetc(file)) == '*') {
            // Start of multi-line comment
            inComment = 1;
        } else if (inComment && ch == '*' && (ch = fgetc(file)) == '/') {
            // End of multi-line comment
            inComment = 0;
        } else if (!inComment && ch == '/' && (ch = fgetc(file)) == '/') {
            // Start of single-line comment
            while ((ch = fgetc(file)) != EOF && ch != '\n');
        } else if (!inComment) {
            if (isDelimiter(ch) || isOperator(ch)) {
                if (index > 0) {
                    buffer[index] = '\0';
                    classifyToken(buffer);
                    index = 0;
                }
                if (isOperator(ch)) {
                    printf("Operator: %c\n", ch);
                } else if (isDelimiter(ch) && !isspace(ch)) {
                    printf("Punctuation: %c\n", ch);
                }
            } else if (!isspace(ch) || ch == '\n') {
                buffer[index++] = ch;
            }
        }
    }
    if (index > 0) {
        buffer[index] = '\0';
        classifyToken(buffer);
    }

    fclose(file);

    // Print the symbol table
    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i]);
    }
}

// Main function
int main() {
    char filename[100];
    printf("Enter the C source code file name: ");
    scanf("%s", filename);

    lexicalAnalyzer(filename);

    return 0;
}
