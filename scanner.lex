%{
/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap

digit       [0-9]
letter      [a-zA-Z]
whitespace  [\t\n ]
cmp_operator  (==|!=|<=|>=|<|>)
binary_operator   [+\-*/]
comment          [.\a]
identifier       [.\b]
number           [.\c]
string           [.\d]

%%


void        return VOID;
int         return INT;
byte        return BYTE;
bool        return BOOL;
and         return AND;
or          return OR;
not         return NOT;
true        return TRUE;
false       return FALSE;
return      return RETURN;
if          return IF;
else        return ELSE;
while       return WHILE;
break       return BREAK;
continue    return CONTINUE;
;           return SC;
,           return COMMA;
"("          return LPAREN;
")"           return RPAREN;
{           return LBRACE;
}           return RBRACE;
"["           return LBRACK;
"]"           return RBRACK;
=           return ASSIGN;
{cmp_operator}      return RELOP;
{binary_operator}   return BINOP;
{comment}           return COMMENT;
{identifier}        return ID;
{number}            return NUM;
{string}            return STRING;

{whitespace}            ;

.                       printf("Lex doesn't know what that is!\n");

%%

