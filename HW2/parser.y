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

%token RelOp_Equal
%token RelOp_Not_Equal
%token RelOp_Greather_Equal
%token RelOp_Less_Equal
%token RelOp_Greather
%token RelOp_Less

%left BINOP_PLUS
%left BINOP_MINUS
%left BINOP_DIV
%left BINOP_MUL

%token ID
%token NUM
%token NUM_B
%token STRING;


// TODO: Define precedence and associativity here

%%

// While reducing the start variable, set the root of the AST
Program: Funcs                { program = $1; };

Funcs: FuncDecl Funcs         {$$ = $2; $$->push_front($1);}
     | /* epsilon */          {$$ = std::shared_ptr(new ast::Funcs())};

FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE {$$ = std::shared_ptr(new FuncDecl($2, $1, $4, $7))};

RetType: Type                 {$$ = $1}
       | VOID                 {$$ = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::VOID));}
Formals: /* epsilon */        {$$ = std::shared_ptr(new ast::Formals())}
       | FormalsList          { };

FormalsList: FormalDecl       {$$ = std::shared_ptr(new ast::Formals($1))}
           | FormalDecl COMMA FormalsList {$$ = $3;
                                           $$->push_front($1);};

FormalDecl: Type ID           {$$ = std::shared_ptr(new ast::Formal($2,$1))};

Statements: Statement            {$$ = std::shared_ptr(new ast::Statements($1));}
          | Statements Statement {$$ = $1;
                                  $$->push_back($2);};

Statement: LBRACE Statements RBRACE                       {$$ = $1;}
         | Type ID SC                                     {$$ = std::shared_ptr(new ast::VarDecl($2, $1));}
         | Type ID ASSIGN Exp SC                          {$$ = std::shared_ptr(new ast::VarDecl($2, $1, $4));}
         | ID ASSIGN Exp SC                               {$$ = std::shared_ptr(new ast::Assign($1, $3));}
         | ID LBRACK Exp RBRACK ASSIGN Exp SC             {$$ = std::shared_ptr(new ast::ArrayAssign($1, $6, $3));}
         | Type ID LBRACK Exp RBRACK SC                   {$$ = std::shared_ptr(new ast::ArrayType($1->type,$4));}
         | Call SC                                        {$$ = $1}
         | RETURN SC                                      {$$ = std::shared_ptr(new ast::Return());}
         | RETURN Exp SC                                  {$$ = std::shared_ptr(new ast::Return($2));}
         | IF LPAREN Exp RPAREN Statement                 {$$ = std::shared_ptr(new ast::If($3, $5));}
         | IF LPAREN Exp RPAREN Statement ELSE Statement  {$$ = std::shared_ptr(new ast::If($3, $5, $7));}
         | WHILE LPAREN Exp RPAREN Statement              {$$ = std::shared_ptr(new ast::While($3, $5));}
         | BREAK SC                                       {$$ = std::shared_ptr(new ast::Break());}
         | CONTINUE SC                                    {$$ = std::shared_ptr(new ast::Continue());};

Call: ID LPAREN ExpList RPAREN    {$$ = std::shared_ptr(new ast::Call($1, $3));}
    | ID LPAREN RPAREN            {$$ = std_shared_ptr(new ast::Call($1))};

ExpList: Exp                      {$$ = std::shared_ptr(new ast::ExpList($1));}
       | Exp COMMA ExpList        {$$ = $3;
                                   $$->push_front($1);};

Type: INT                         {$$ = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::INT));}
    | BYTE                        {$$ = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::BYTE));}
    | BOOL                        {$$ = std::shared_ptr(new ast::PrimitiveType(ast::BuiltInType::BOOL));};

Exp: LPAREN Exp RPAREN                          {$$ = $1;}
   | ID LBRACK Exp RBRACK                       {$$ = std::shared_ptr(new ast::ArrayDereference($1, $3));}
   | Exp BINOP_ADD Exp                          {$$ = std::shared_ptr(new ast::BinOp($1, $3, ast::BinOpType::ADD));}
   | Exp BINOP_SUB Exp                          {$$ = std::shared_ptr(new ast::BinOp($1, $3, ast::BinOpType::SUB));}
   | Exp BINOP_MUL Exp                          {$$ = std::shared_ptr(new ast::BinOp($1, $3, ast::BinOpType::MUL));}
   | Exp BINOP_DIV Exp                          {$$ = std::shared_ptr(new ast::BinOp($1, $3, ast::BinOpType::DIV));}
   | ID                                         {$$ = $1;}
   | Call                                       {$$ = $1;}
   | NUM                                        {$$ = $1;}
   | NUM_B                                      {$$ = $1;}
   | STRING                                     {$$ = $1;}
   | TRUE                                       {$$ = $1;}
   | FALSE                                      {$$ = $1;}
   | NOT Exp                                    {$$ = std::shared_ptr(new ast::Not($2));}
   | Exp AND Exp                                {$$ = std::shared_ptr(new ast::And($1, $3));}
   | Exp OR Exp                                 {$$ = std::shared_ptr(new ast::($1, $3));}
   | Exp RelOp_EQ Exp                           {$$ = std::shared_ptr(new ast::RelOp($1, $3, ast::RelOpType::EQ));}
   | Exp RelOp_NE Exp                           {$$ = std::shared_ptr(new ast::RelOp($1, $3, ast::RelOpType::NE));}
   | Exp RelOp_LT Exp                           {$$ = std::shared_ptr(new ast::RelOp($1, $3, ast::RelOpType::LT));}
   | Exp RelOp_GT Exp                           {$$ = std::shared_ptr(new ast::RelOp($1, $3, ast::RelOpType::GT));}
   | Exp RelOp_LE Exp                           {$$ = std::shared_ptr(new ast::RelOp($1, $3, ast::RelOpType::LE));}
   | Exp RelOp_GE Exp                           {$$ = std::shared_ptr(new ast::RelOp($1, $3, ast::RelOpType::GE));}
   | LPAREN Type RPAREN Exp                     {$$ = std::shared_ptr(new ast::Cast($4, std::dynamic_pointer_cast<ast::PrimitiveType>($2)));};


%%

// TODO: Place any additional code here
