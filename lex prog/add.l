%option noyywrap
%{
#include <stdio.h>
int v=0, c=0;
%}

%%

[aeiouAEIOU] { v++; }                      // Count vowels
[a-z A-Z] { c++; }   // Count consonants
[0-9]+ { printf("%s\n", yytext); }          // Match and print numbers
.|\n { }                                    // Ignore other characters and newline

%%

int main() {
    printf("Enter the data: ");
    yylex();  // Start the lexical analysis
    printf("\nVowel count: %d\n", v);
    printf("Consonant count: %d\n", c);
    return 0;
}