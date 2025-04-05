%{
/* Declarations section */
#include <stdio.h>
#include "output.hpp"
%}

%option yylineno
%option noyywrap

digit                   [0-9]
char                    [a-zA-Z]
chars_and_digits        [a-zA-Z][0-9]

non_zero_digit          [1-9]
relations               ==|!=|<=|>=|<|>
binary                  \+|\-|\*|\/
whitespace              [\t\n ]

%x COMMENT_MODE
%x STRING_MODE

%%

void                                return tokentype::VOID;
int                                 return tokentype::INT;
byte                                return tokentype::BYTE;
bool                                return tokentype::BOOL;
and                                 return tokentype::AND;
or                                  return tokentype::OR;
not                                 return tokentype::NOT;
true                                return tokentype::TRUE;
false                               return tokentype::FALSE;
return                              return tokentype::RETURN;
if                                  return tokentype::IF;
else                                return tokentype::ELSE;
while                               return tokentype::WHILE;
break                               return tokentype::BREAK;
continue                            return tokentype::CONTINUE;
;                                   return tokentype::SC;
,                                   return tokentype::COMMA;
\(                                  return tokentype::LPAREN;
\)                                  return tokentype::RPAREN;
\{                                  return tokentype::LBRACE;
\}                                  return tokentype::RBRACE;
\[                                  return tokentype::LBRACK;
\]                                  return tokentype::RBRACK;
=                                   return tokentype::ASSIGN;
{relations}                         return tokentype::RELOP;
{binary}                            return tokentype::BINOP;
\/\/                                BEGIN(COMMENT_MODE);
<COMMENT_MODE>[\n|\r|\r\n]*         BEGIN(INITIAL);
<COMMENT_MODE>.                     ;
{char}({char}|{digit})*             return tokentype::ID;
{non_zero_digit}{digit}*|0          return tokentype::NUM;
\"                                  BEGIN(STRING_MODE);
<STRING_MODE>\\\"                   return tokentype::STRING;
<STRING_MODE>\"                     BEGIN(INITIAL);
<STRING_MODE>[^\"]*                 return tokentype::STRING;
{whitespace}                        ;

%%
