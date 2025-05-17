%{
/* Declarations section */
#include <stdio.h>
#include "output.hpp"
#include "nodes.hpp"
#include "parser.tab.h"


%}

%option yylineno
%option noyywrap

whitespace                   [\r\t\n ]|\r\n

%%

void        					{yylval = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::VOID); return VOID;};
int         					{yylval = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::INT);  return INT;};
byte        					{yylval = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::BYTE); return BYTE;};
bool        					{yylval = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::BOOL); return BOOL;};
and         					{return AND;};
or          					{return OR;};
not         					{return NOT;};
true        					{yylval = std::make_shared<ast::Bool>(true); return TRUE;};
false       					{yylval = std::make_shared<ast::Bool>(false); return FALSE;};
return      					{return RETURN;};
if          					{return IF;};
else        					{return ELSE;};
while       					{return WHILE;};
break       					{yylval = std::make_shared<ast::Break>(); return BREAK;};
continue    					{yylval = std::make_shared<ast::Continue>(); return CONTINUE;};
;           					{return SC;};
,           					{return COMMA;};
\(         						{return LPAREN;};
\)         						{return RPAREN;};
\{         						{return LBRACE;};
\}         						{return RBRACE;};
\[        		 				{return LBRACK;};
\]         						{return RBRACK;};
=           					{return ASSIGN;};
==      	                    {return ast::RelOpType::EQ;};
!=      	                    {return ast::RelOpType::NE;};
\<=     	                    {return ast::RelOpType::LE;};
>=      	                    {return ast::RelOpType::GE;};
\<                              {return ast::RelOpType::LT;};
>      	                        {return ast::RelOpType::GT;};

\+  			                {return BINOP_ADD;};
\- 			                    {return BINOP_SUB;};
\*			                    {return BINOP_MUL;};
\/   			                {return BINOP_DIV;};


[a-zA-Z][a-zA-Z0-9]*            {yylval = std::make_shared<ast::ID>(yytext);  return ID;};
0 | [1-9][0-9]*                 {yylval = std::make_shared<ast::Num>(yytext); return NUM;};
0b | [1-9][0-9]*b               {yylval = std::make_shared<ast::NumB>(yytext);return NUM_B;};

\"([^\n\r\"\\]|\\[rnt"\\])+\"	{yylval = std::make_shared<ast::String>(yytext); return STRING;};



{whitespace} | //[^\r\n]*[\r|\n|\r\n]?        ;


.                               {output::errorLex(yylineno);};


%%