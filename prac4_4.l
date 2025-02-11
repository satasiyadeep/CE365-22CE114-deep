%option noyywrap
%{
#include <stdio.h>
#include <stdbool.h>

bool has_lower = false;
bool has_upper = false;
bool has_digit = false;
bool has_symbol = false;
int length = 0;

void reset_flags() {
    has_lower = has_upper = has_digit = has_symbol = false;
    length = 0;
}
%}

%%

[a-z]       { has_lower = true; length++; }
[A-Z]       { has_upper = true; length++; }
[0-9]       { has_digit = true; length++; }
[*;#$@]     { has_symbol = true; length++; }
[^a-zA-Z0-9*;#$@\n] { length++; } // Count other characters excluding newline

\n          {  
    if (length >= 9 && length <= 15 && has_lower && has_upper && has_digit && has_symbol) {
        printf("Password is valid.\n");
    } else {
        printf("Password is invalid. It must be 9-15 characters long and include at least one lowercase letter, one uppercase letter, one digit, and one symbol (*, ;, #, $, @).\n");
    }
    reset_flags();
}

%%

int main() {
    printf("Enter your password: ");
    yylex();
    return 0;
}
