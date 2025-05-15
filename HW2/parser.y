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
%token TRUE
%token FALSE
%token RETURN
%token IF
%right ELSE
%token WHILE
%token BREAK
%token CONTINUE
%token SC
%left COMMA
%left LPAREN
%left RPAREN
%left LBRACE
%left RBRACE
%left LBRACK
%left RBRACK
%right ASSIGN

%token ID
%token NUM
%token NUM_B
%token STRING;

%right BINOP_ADD
%right BINOP_SUB
%left BINOP_DIV
%left BINOP_MUL

%right NOT
%left AND
%left OR

%left RelOp_EQ
%left RelOp_NE
%left RelOp_LT
%left RelOp_GT
%left RelOp_LE
%left RelOp_GE



// TODO: Define precedence and associativity here

%%

// While reducing the start variable, set the root of the AST
Program: Funcs                { program = $1; };

Funcs: FuncDecl Funcs         {$$ = $2; 
                                   const auto const_first = std::make_shared<ast::Exp>($1);
                                   std::dynamic_pointer_cast<ast::ExpList>($$)->push_front(const_first);};
     | /* epsilon */          {$$ = std::make_shared<ast::Funcs>();};

FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE { $$ = std::make_shared<ast::FuncDecl>($2, $1, $4, $7); };

RetType: Type                             { $$ = $1; }
  | VOID                                  { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::VOID); }

Formals: /* epsilon */                    { $$ = std::make_shared<ast::Formals>(); }
  | FormalsList                           { /* $$ already set by FormalsList */ }

FormalsList: FormalDecl                   { $$ = std::make_shared<ast::Formals>($1); }
  | FormalDecl COMMA FormalsList          { $$ = $3; 
                                                 const auto const_first = std::make_shared<ast::Exp>($1);
                                                 std::dynamic_pointer_cast<ast::ExpList>($$)->push_front(const_first);};

FormalDecl: Type ID                       { $$ = std::make_shared<ast::Formal>($2, $1); }

Statements: Statement                     { $$ = std::make_shared<ast::Statements>($1); }
  | Statements Statement                  { $$ = $1; 
                                                 const auto const_second = std::make_shared<ast::Exp>($2);
                                                 std::dynamic_pointer_cast<ast::ExpList>($$)->push_front(const_second);};

Statement: LBRACE Statements RBRACE              { $$ = $2; }
  | Type ID SC                            { $$ = std::make_shared<ast::VarDecl>($2, $1); }
  | Type ID ASSIGN Exp SC                 { $$ = std::make_shared<ast::VarDecl>($2, $1, $4); }
  | ID ASSIGN Exp SC                      { $$ = std::make_shared<ast::Assign>($1, $3); }
  | ID LBRACK Exp RBRACK ASSIGN Exp SC    { $$ = std::make_shared<ast::ArrayAssign>($1, $6, $3); }
  | Type ID LBRACK Exp RBRACK SC          { $$ = std::make_shared<ast::ArrayType>(std::make_shared<ast::Type>($1)->type, $4); }
  | Call SC                               { $$ = $1; }
  | RETURN SC                             { $$ = std::make_shared<ast::Return>(); }
  | RETURN Exp SC                         { $$ = std::make_shared<ast::Return>($2); }
  | IF LPAREN Exp RPAREN Statement                      { $$ = std::make_shared<ast::If>($3, $5); }
  | IF LPAREN Exp RPAREN Statement ELSE Statement       { $$ = std::make_shared<ast::If>($3, $5, $7); }
  | WHILE LPAREN Exp RPAREN Statement     { $$ = std::make_shared<ast::While>($3, $5); }
  | BREAK SC                              { $$ = std::make_shared<ast::Break>(); }
  | CONTINUE SC                           { $$ = std::make_shared<ast::Continue>(); }

Call:ID LPAREN ExpList RPAREN             { $$ = std::make_shared<ast::Call>($1, $3); }
  | ID LPAREN RPAREN                      { $$ = std::make_shared<ast::Call>($1); }

ExpList: Exp                              { $$ = std::make_shared<ast::ExpList>($1); }
  | Exp COMMA ExpList                     { $$ = $3; 
                                                 const auto const_first = std::make_shared<ast::Exp>($1);
                                                 std::dynamic_pointer_cast<ast::ExpList>($$)->push_front(const_first);};

Type:  INT                                { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::INT); }
  | BYTE                                  { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::BYTE); }
  | BOOL                                  { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::BOOL); }

Exp: LPAREN Exp RPAREN                    { $$ = $2; }
  | ID LBRACK Exp RBRACK                  { $$ = std::make_shared<ast::ArrayDereference>($1, $3); }
  | Exp BINOP_ADD Exp                     { $$ = std::make_shared<ast::BinOp>($1, $3, ast::BinOpType::ADD); }
  | Exp BINOP_SUB Exp                     { $$ = std::make_shared<ast::BinOp>($1, $3, ast::BinOpType::SUB); }
  | Exp BINOP_MUL Exp                     { $$ = std::make_shared<ast::BinOp>($1, $3, ast::BinOpType::MUL); }
  | Exp BINOP_DIV Exp                     { $$ = std::make_shared<ast::BinOp>($1, $3, ast::BinOpType::DIV); }
  | ID                                    { $$ = $1; }
  | Call                                  { $$ = $1; }
  | NUM                                   { $$ = $1; }
  | NUM_B                                 { $$ = $1; }
  | STRING                                { $$ = $1; }
  | TRUE                                  { $$ = $1; }
  | FALSE                                 { $$ = $1; }
  | NOT Exp                               { $$ = std::make_shared<ast::Not>($2); }
  | Exp AND Exp                           { $$ = std::make_shared<ast::And>($1, $3); }
  | Exp OR Exp                            { $$ = std::make_shared<ast::Or>($1, $3); }
  | Exp RelOp_EQ Exp                      { $$ = std::make_shared<ast::RelOp>($1, $3, ast::RelOpType::EQ); }
  | Exp RelOp_NE Exp                      { $$ = std::make_shared<ast::RelOp>($1, $3, ast::RelOpType::NE); }
  | Exp RelOp_LT Exp                      { $$ = std::make_shared<ast::RelOp>($1, $3, ast::RelOpType::LT); }
  | Exp RelOp_GT Exp                      { $$ = std::make_shared<ast::RelOp>($1, $3, ast::RelOpType::GT); }
  | Exp RelOp_LE Exp                      { $$ = std::make_shared<ast::RelOp>($1, $3, ast::RelOpType::LE); }
  | Exp RelOp_GE Exp                      { $$ = std::make_shared<ast::RelOp>($1, $3, ast::RelOpType::GE); }
  | LPAREN Type RPAREN Exp                { auto prim = std::dynamic_pointer_cast<ast::PrimitiveType>($2);
                                            $$ = std::make_shared<ast::Cast>($4, prim);};


%%

// TODO: Place any additional code here
