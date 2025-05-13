%{

#include "nodes.hpp"
#include "output.hpp"

// bison declarations
extern int yylineno;
extern int yylex();

void yyerror(const char*);

// root of the AST, set by the parser and used by other parts of the compiler
std::shared_ptr<ast::Node> program;

using namespace std;

// TODO: Place any additional declarations here
%}

%token VOID
%token INT
%token BYTE
%token BOOL
%token AND
%token OR
%token NOT
%token TRUE
%token FALSE
%token RETURN
%token IF
%token ELSE
%token WHILE
%token BREAK
%token CONTINUE
%token SC
%token COMMA
%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token LBRACK
%token RBRACK
%token ASSIGN
%token RELOP
%token BINOP
%token ID
%token NUM
%token NUM_B
%token STRING;


// TODO: Define precedence and associativity here

%%

// While reducing the start variable, set the root of the AST
Program: Funcs                { program = $1; };

Funcs: FuncDecl Funcs         { }
     | /* epsilon */          { };

FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE { };

RetType: Type                 { }
       | VOID                 { };

Formals: /* epsilon */        { }
       | FormalsList          { };

FormalsList: FormalDecl       { }
           | FormalDecl COMMA FormalsList { };

FormalDecl: Type ID           { };

Statements: Statement         { }
          | Statements Statement { };

Statement: LBRACE Statements RBRACE                       { }
         | Type ID SC                                     { }
         | Type ID ASSIGN Exp SC                          { }
         | ID ASSIGN Exp SC                               { }
         | ID LBRACK Exp RBRACK ASSIGN Exp SC             { }
         | Type ID LBRACK Exp RBRACK SC                   { }
         | Call SC                                        { }
         | RETURN SC                                      { }
         | RETURN Exp SC                                  { }
         | IF LPAREN Exp RPAREN Statement                 { }
         | IF LPAREN Exp RPAREN Statement ELSE Statement  { }
         | WHILE LPAREN Exp RPAREN Statement              { }
         | BREAK SC                                       { }
         | CONTINUE SC                                    { };

Call: ID LPAREN ExpList RPAREN    { }
    | ID LPAREN RPAREN            { };

ExpList: Exp                      { }
       | Exp COMMA ExpList        { };

Type: INT                         { }
    | BYTE                        { }
    | BOOL                        { };

Exp: LPAREN Exp RPAREN                          { }
   | ID LBRACK Exp RBRACK                       { }
   | Exp BINOP Exp                              { }
   | ID                                         { }
   | Call                                       { }
   | NUM                                        { }
   | NUM_B                                      { }
   | STRING                                     { }
   | TRUE                                       { }
   | FALSE                                      { }
   | NOT Exp                                    { }
   | Exp AND Exp                                { }
   | Exp OR Exp                                 { }
   | Exp RELOP Exp                              { }
   | LPAREN Type RPAREN Exp                     { };


%%

// TODO: Place any additional code here