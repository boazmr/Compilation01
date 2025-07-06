#include "output.hpp"
#include "nodes.hpp"
#include <iostream>

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
      output::SemanticVisitor semanticVisitor;
      program->accept(semanticVisitor);
      semanticVisitor.first_run = false;
      program->accept(semanticVisitor);
      // std::cout << semanticVisitor.scopePrinter;
      code_global_funcs();
      program->accept(semanticVisitor);

      semanticVisitor.buffer.emitString("printi");
      semanticVisitor.buffer.emitString("print");
      semanticVisitor.buffer.emitString("readi");
      std::cout << semanticVisitor.buffer;


    }
}