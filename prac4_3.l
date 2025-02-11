%{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
%}

%%
[^\t\n ]+    { word_count++; char_count += yyleng; } // Matches words
[ \t]+       { char_count += yyleng; } // Matches spaces/tabs
\n           { line_count++; char_count++; } // Matches new lines
%%

int main() {
    printf("Enter text (Ctrl+Z to stop input):\n");
    yylex();
    
    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);
    return 0;
}

int yywrap() {
    return 1;
}