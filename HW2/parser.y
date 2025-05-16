%{

#include "nodes.hpp"
#include "output.hpp"

// bison declarations
extern int yylineno;
extern int yylex();

 void yyerror (char const *s);

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
%nonassoc LOWER_THAN_ELSE
%right ELSE
%token IF
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

Funcs: /* epsilon */          {$$ = std::make_shared<ast::Funcs>();}; 
  | FuncDecl Funcs         {$$ = $2;
                                   const auto const_first = std::dynamic_pointer_cast<ast::FuncDecl>($1);
                                   std::dynamic_pointer_cast<ast::Funcs>($$)->push_front(const_first);};

FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE { 
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($2);
        auto Type_ptr = std::dynamic_pointer_cast<ast::Type>($1);
        auto Formals_ptr = std::dynamic_pointer_cast<ast::Formals>($4);
        auto Statements_ptr = std::dynamic_pointer_cast<ast::Statements>($7);
        $$ = std::make_shared<ast::FuncDecl>(ID_ptr, Type_ptr, Formals_ptr, Statements_ptr);
};

RetType: Type                             { $$ = $1; }
  | VOID                                  { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::VOID); }

Formals: /* epsilon */                    { $$ = std::make_shared<ast::Formals>(); }
  | FormalsList                           { $$ = $1; }

FormalsList: FormalDecl                   { auto formals = std::make_shared<ast::Formals>();
                                            formals->push_front(std::dynamic_pointer_cast<ast::Formal>($1));
                                            $$ = formals;}
  | FormalDecl COMMA FormalsList          { auto formals = std::dynamic_pointer_cast<ast::Formals>($3);
                                            formals->push_front(std::dynamic_pointer_cast<ast::Formal>($1));
                                            $$ = formals;};

FormalDecl: Type ID                       { 
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($2);
        auto Type_ptr = std::dynamic_pointer_cast<ast::Type>($1);
        $$ = std::make_shared<ast::Formal>(ID_ptr, Type_ptr); 
};

Statements: Statement                     { 
        auto statements = std::make_shared<ast::Statements>();
        statements->push_front(std::dynamic_pointer_cast<ast::Statement>($1));
        $$ = statements; }
  | Statements Statement                  { 
        auto statements = std::dynamic_pointer_cast<ast::Statements>($1);
        statements->push_front(std::dynamic_pointer_cast<ast::Statement>($2));
        $$ = statements;};

Statement: LBRACE Statements RBRACE              { $$ = $2; }
  | Type ID SC                            {  
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($2);
        auto Type_ptr = std::dynamic_pointer_cast<ast::Type>($1);
        $$ = std::make_shared<ast::VarDecl>(ID_ptr, Type_ptr); }
  | Type ID ASSIGN Exp SC                 {
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($2);
        auto Type_ptr = std::dynamic_pointer_cast<ast::Type>($1);
        auto Value_ptr = std::dynamic_pointer_cast<ast::Exp>($4);
        $$ = std::make_shared<ast::VarDecl>(ID_ptr, Type_ptr, Value_ptr); }
  | ID ASSIGN Exp SC                      { 
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($1);
        auto Value_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::Assign>(ID_ptr, Value_ptr); }
  | ID LBRACK Exp RBRACK ASSIGN Exp SC    { 
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($1);
        auto Index_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($6);
        $$ = std::make_shared<ast::ArrayAssign>(ID_ptr, Exp_ptr, Index_ptr); }
  | Type ID LBRACK Exp RBRACK SC          { 
        auto Type_ptr = std::dynamic_pointer_cast<ast::Type>($1);
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($4);
        ast::BuiltInType base_type;
        if (auto prim = std::dynamic_pointer_cast<ast::PrimitiveType>(Type_ptr)) {
          base_type = prim->type;
        } else{
          auto arr = std::dynamic_pointer_cast<ast::ArrayType>(Type_ptr);
          base_type = arr->type;
        }
        $$ = std::make_shared<ast::ArrayType>(base_type, Exp_ptr); }
  | Call SC                               { $$ = $1; }
  | RETURN SC                             { $$ = std::make_shared<ast::Return>(); }
  | RETURN Exp SC                         { 
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($2);
        $$ = std::make_shared<ast::Return>(Exp_ptr); }
  | IF LPAREN Exp RPAREN Statement %prec LOWER_THAN_ELSE                     { 
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        auto Statement_ptr = std::dynamic_pointer_cast<ast::Statement>($5);
        $$ = std::make_shared<ast::If>(Exp_ptr, Statement_ptr); }
  | IF LPAREN Exp RPAREN Statement ELSE Statement       { 
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        auto If_Statement_ptr = std::dynamic_pointer_cast<ast::Statement>($5);
        auto Else_Statement_ptr = std::dynamic_pointer_cast<ast::Statement>($7);
        $$ = std::make_shared<ast::If>(Exp_ptr, If_Statement_ptr, Else_Statement_ptr); }
  | WHILE LPAREN Exp RPAREN Statement     { 
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        auto Statement_ptr = std::dynamic_pointer_cast<ast::Statement>($5);
        $$ = std::make_shared<ast::While>(Exp_ptr, Statement_ptr); }
  | BREAK SC                              { $$ = std::make_shared<ast::Break>(); }
  | CONTINUE SC                           { $$ = std::make_shared<ast::Continue>(); }

Call: ID LPAREN ExpList RPAREN             { 
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($1);
        auto ExpList_ptr = std::dynamic_pointer_cast<ast::ExpList>($3);
        $$ = std::make_shared<ast::Call>(ID_ptr, ExpList_ptr); }
  | ID LPAREN RPAREN                      { 
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($1);
        $$ = std::make_shared<ast::Call>(ID_ptr); }

ExpList: Exp                              { 
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        $$ = std::make_shared<ast::ExpList>(Exp_ptr); }
  | Exp COMMA ExpList                     { 
        auto expression_list = std::dynamic_pointer_cast<ast::ExpList>($3);
        expression_list->push_front(std::dynamic_pointer_cast<ast::Exp>($1));
        $$ = expression_list; }

Type:  INT                                { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::INT); }
  | BYTE                                  { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::BYTE); }
  | BOOL                                  { $$ = std::make_shared<ast::PrimitiveType>(ast::BuiltInType::BOOL); }

Exp: LPAREN Exp RPAREN                    { $$ = $2; }
  | ID LBRACK Exp RBRACK                  { 
        auto ID_ptr = std::dynamic_pointer_cast<ast::ID>($1);
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::ArrayDereference>(ID_ptr, Exp_ptr); }
  | Exp BINOP_ADD Exp                     { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::BinOp>(First_Exp_ptr, Second_Exp_ptr, ast::BinOpType::ADD); }
  | Exp BINOP_SUB Exp                     { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::BinOp>(First_Exp_ptr, Second_Exp_ptr, ast::BinOpType::SUB); }
  | Exp BINOP_MUL Exp                     { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::BinOp>(First_Exp_ptr, Second_Exp_ptr, ast::BinOpType::MUL); }
  | Exp BINOP_DIV Exp                     { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::BinOp>(First_Exp_ptr, Second_Exp_ptr, ast::BinOpType::DIV); }
  | ID                                    { $$ = $1; }
  | Call                                  { $$ = $1; }
  | NUM                                   { $$ = $1; }
  | NUM_B                                 { $$ = $1; }
  | STRING                                { $$ = $1; }
  | TRUE                                  { $$ = $1; }
  | FALSE                                 { $$ = $1; }
  | NOT Exp                               { 
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($2);
        $$ = std::make_shared<ast::Not>(Exp_ptr); }
  | Exp AND Exp                           { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::And>(First_Exp_ptr, Second_Exp_ptr); }
  | Exp OR Exp                            { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::Or>(First_Exp_ptr, Second_Exp_ptr); }
  | Exp RelOp_EQ Exp                      { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::RelOp>(First_Exp_ptr, Second_Exp_ptr, ast::RelOpType::EQ); }
  | Exp RelOp_NE Exp                      {  
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::RelOp>(First_Exp_ptr, Second_Exp_ptr, ast::RelOpType::NE); }
  | Exp RelOp_LT Exp                      { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::RelOp>(First_Exp_ptr, Second_Exp_ptr, ast::RelOpType::LT); }
  | Exp RelOp_GT Exp                      { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::RelOp>(First_Exp_ptr, Second_Exp_ptr, ast::RelOpType::GT); }
  | Exp RelOp_LE Exp                      { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::RelOp>(First_Exp_ptr, Second_Exp_ptr, ast::RelOpType::LE); }
  | Exp RelOp_GE Exp                      { 
        auto First_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($1);
        auto Second_Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($3);
        $$ = std::make_shared<ast::RelOp>(First_Exp_ptr, Second_Exp_ptr, ast::RelOpType::GE); }
  | LPAREN Type RPAREN Exp                { 
        auto Prim_ptr = std::dynamic_pointer_cast<ast::PrimitiveType>($2);
        auto Exp_ptr = std::dynamic_pointer_cast<ast::Exp>($4);
        $$ = std::make_shared<ast::Cast>(Exp_ptr, Prim_ptr);};


%%

// TODO: Place any additional code here
