%{
/* Declarations section */
#include <stdio.h>
#include "output.hpp"
#include "parser.tab.h"

%}

%option yylineno
%option noyywrap

whitespace                   [\r\t\n ]|\r\n

%%

void        					{yylval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::VOID)); return VOID;};
int         					{yylval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::INT)); return INT;};
byte        					{yylval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::BYTE)); return BYTE;};
bool        					{yylval = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::BOOL)); return BOOL;};
and         					{/*to do*/ return AND;};
or          					{/*to do*/ return OR;};
not         					{/*to do*/ return NOT;};
true        					{yylval = std::shared_ptr(new ast::Bool(true)); return TRUE;};
false       					{yylval = std::shared_ptr(new ast::Bool(false)); return FALSE;};
return      					{/*to do*/ return RETURN;};
if          					{/*to do*/ return IF;};
else        					{/*to do*/ return ELSE;};
while       					{/*to do*/ return WHILE;};
break       					{yylval = std::shared_ptr(new ast::Break()); return BREAK;};
continue    					{yylval = std::shared_ptr(new ast::Continue()); return CONTINUE;};
;           					{/*to do*/ return SC;};
,           					{/*to do*/ return COMMA;};
\(         						{/*to do*/ return LPAREN;};
\)         						{/*to do*/ return RPAREN;};
\{         						{/*to do*/ return LBRACE;};
\}         						{/*to do*/ return RBRACE;};
\[        		 				{/*to do*/ return LBRACK;};
\]         						{/*to do*/ return RBRACK;};
=           					{/*to do*/return ASSIGN;};
==|!=|<=|>=|<|>      	        {/*to do*/ return RelOp;};
\+|\-|\*|\/   			        {/*to do*/ return BINOP;};

[a-zA-Z][a-zA-Z0-9]*            {yylval = std::shared_ptr(new ast::ID(yytext)); return ID;};
0 | [1-9][0-9]*                 {yylval = std::shared_ptr(new ast::Num(yytext)); return NUM;};
0b | [1-9][0-9]*b               {yylval = std::shared_ptr(new ast::NumB(yytext) ;return NUM_B;};

\"([^\n\r\"\\]|\\[rnt"\\])+\"	{yylval = std::shared_ptr(new ast::String(yytext)); return STRING;};



{whitespace} | //[^\r\n]*[\r|\n|\r\n]?        ;


.                               {output::errorLex(yylineno);};


%%
