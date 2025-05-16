/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VOID = 258,                    /* VOID  */
    INT = 259,                     /* INT  */
    BYTE = 260,                    /* BYTE  */
    BOOL = 261,                    /* BOOL  */
    TRUE = 262,                    /* TRUE  */
    FALSE = 263,                   /* FALSE  */
    RETURN = 264,                  /* RETURN  */
    LOWER_THAN_ELSE = 265,         /* LOWER_THAN_ELSE  */
    ELSE = 266,                    /* ELSE  */
    IF = 267,                      /* IF  */
    WHILE = 268,                   /* WHILE  */
    BREAK = 269,                   /* BREAK  */
    CONTINUE = 270,                /* CONTINUE  */
    SC = 271,                      /* SC  */
    COMMA = 272,                   /* COMMA  */
    LPAREN = 273,                  /* LPAREN  */
    RPAREN = 274,                  /* RPAREN  */
    LBRACE = 275,                  /* LBRACE  */
    RBRACE = 276,                  /* RBRACE  */
    LBRACK = 277,                  /* LBRACK  */
    RBRACK = 278,                  /* RBRACK  */
    ASSIGN = 279,                  /* ASSIGN  */
    ID = 280,                      /* ID  */
    NUM = 281,                     /* NUM  */
    NUM_B = 282,                   /* NUM_B  */
    STRING = 283,                  /* STRING  */
    BINOP_ADD = 284,               /* BINOP_ADD  */
    BINOP_SUB = 285,               /* BINOP_SUB  */
    BINOP_DIV = 286,               /* BINOP_DIV  */
    BINOP_MUL = 287,               /* BINOP_MUL  */
    NOT = 288,                     /* NOT  */
    AND = 289,                     /* AND  */
    OR = 290,                      /* OR  */
    RelOp_EQ = 291,                /* RelOp_EQ  */
    RelOp_NE = 292,                /* RelOp_NE  */
    RelOp_LT = 293,                /* RelOp_LT  */
    RelOp_GT = 294,                /* RelOp_GT  */
    RelOp_LE = 295,                /* RelOp_LE  */
    RelOp_GE = 296                 /* RelOp_GE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
