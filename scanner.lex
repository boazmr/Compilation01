<<<<<<< HEAD
%{
/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap

digit                           [0-9]
digit_no_zero                   [1-9]
letter                          [a-zA-Z]
whitespace                      [\t\n ]
end_line                        \n|\r|\r\n
cmp_operator                    ==|!=|<=|>=|<|>
binary_operator                 \+|\-|\*|\/
escaped_quote                   \\\"                     
printable_not_quote             [\x20-\x21\x23-\x7E]

%x COMMENT_STATE

%%

void        					return VOID;
int         					return INT;
byte        					return BYTE;
bool        					return BOOL;
and         					return AND;
or          					return OR;
not         					return NOT;
true        					return TRUE;
false       					return FALSE;
return      					return RETURN;
if          					return IF;
else        					return ELSE;
while       					return WHILE;
break       					return BREAK;
continue    					return CONTINUE;
;           					return SC;
,           					return COMMA;
\(         						return LPAREN;
\)         						return RPAREN;
\{         						return LBRACE;
\}         						return RBRACE;
\[        		 				return LBRACK;
\]         						return RBRACK;
=           					return ASSIGN;
{cmp_operator}      			return RELOP;
{binary_operator}   			return BINOP;

\/\/           					                        BEGIN(COMMENT_STATE);
<COMMENT_STATE>.           		                        ;
<COMMENT_STATE>{end_line} 		                        { BEGIN(INITIAL); 
                                                        return COMMENT; }	

{letter}({letter}|{digit})*                             return ID;
{digit_no_zero}{digit}*|0                               return NUM;
({digit_no_zero}{digit}*|0)b                            return NUM_B;

\"({escaped_quote}|{printable_not_quote})*\"			return STRING;
\"({escaped_quote}|{printable_not_quote})*              return UNCLOSED_STRING;



{whitespace}        ;

.                   return UNKNOWN_CHAR;

%%
