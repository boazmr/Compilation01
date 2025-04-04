%{
/* Declarations section */
#include <stdio.h>
void showToken(char *);
%}

%option yylineno
%option noywrap

digit       [0-9]
letter      [a-zA-Z]
whitespace  [\t\n ]

%%

{digit}+                showToken("number");
(letter+@{letter}+\.com) showToken("email address");
{whitespace}            ;

.                       printf("Lex doesn't know what that is!\n");

%%

void showToken(char * name) {
    printf("Lex found token = %s\n", name);
    printf("The lexeme is %s\n", yytext);
    printf("Its length is %d\n", yyleng);
}
