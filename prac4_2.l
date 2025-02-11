%option noyywrap
%{
#include <stdio.h>
int v=0, c=0;
%}

%%
charusat  { printf("university"); }
.      { printf("%s", yytext); }
                  

      
.|\n { }                                    // Ignore other characters and newline

%%

int main() {
    printf("Enter the data: ");
    yylex();  // Start the lexical analysis
  
    return 0;
}