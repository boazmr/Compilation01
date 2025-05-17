#include "output.hpp"
#include "nodes.hpp"

// Extern from the bison-generated parser
extern int yyparse();
extern int yylineno;

// Basic implementation of yyerror.
 void yyerror (char const *s) {
   output::errorSyn(yylineno);
 }

extern std::shared_ptr<ast::Node> program;

int main() {
    // Parse the input. The result is stored in the global variable `program`
    yyparse();
    // Print the AST using the PrintVisitor
    if(program){
      output::PrintVisitor printVisitor;
      program->accept(printVisitor);
    }
}