#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <vector>
#include <map>
#include <stack>
#include <string>
#include <sstream>
#include "visitor.hpp"
#include "nodes.hpp"

namespace output {
    /* Error handling functions */

    void errorLex(int lineno);

    void errorSyn(int lineno);

    void errorUndef(int lineno, const std::string &id);

    void errorDefAsFunc(int lineno, const std::string &id);

    void errorUndefFunc(int lineno, const std::string &id);

    void errorDefAsVar(int lineno, const std::string &id);

    void errorDef(int lineno, const std::string &id);

    void errorPrototypeMismatch(int lineno, const std::string &id, std::vector<std::string> &paramTypes);

    void errorMismatch(int lineno);

    void errorUnexpectedBreak(int lineno);

    void errorUnexpectedContinue(int lineno);

    void errorMainMissing();

    void errorByteTooLarge(int lineno, int value);

    void ErrorInvalidAssignArray(int lineno, const std::string &id_arr);

    /* ScopePrinter class
     * This class is used to print scopes in a human-readable format.
     */
    class ScopePrinter {
    private:
        std::stringstream globalsBuffer;
        std::stringstream buffer;
        int indentLevel;

        std::string indent() const;

    public:
        ScopePrinter();

        void beginScope();

        void endScope();

        void emitVar(const std::string &id, const ast::BuiltInType &type, int offset);

        void emitFunc(const std::string &id, const ast::BuiltInType &returnType,
                      const std::vector<ast::BuiltInType> &paramTypes);

        friend std::ostream &operator<<(std::ostream &os, const ScopePrinter &printer);
    };

    enum Type{
        NUMERIC,
        BOOL,
        STRING,

    };

    struct Var_Entry{
        ast::BuiltInType type;
        int offset;
    };

    struct Func_Entry {
        std::vector<ast::BuiltInType> paramTypes;
        ast::BuiltInType returnType;
    };


    struct SymbolTable{
        std::map<std::string, Var_Entry> table;
    };

    /* PrintVisitor class
     * This class is used to print the AST in a human-readable format.
     */
    class SemanticVisitor : public Visitor {
    private:
        // The symbol table, implementad as a scopes stack.
        std::stack<std::shared_ptr<SymbolTable>> symbol_stack;
        // Stack of scopes offsets.
        std::stack<int> offsets;
        // data struct that saves func
        std::map<std::string, Func_Entry> func_table;
        
        ScopePrinter scopePrinter;

    public:
        bool first_run;
        SemanticVisitor();
        std::shared_ptr<SymbolTable> makeTable();
        bool search_var(std::string& name);
        void push_var(const std::string &id, const ast::BuiltInType &type);

        bool search_func(std::string& name);
        void push_func(const std::string &id, const ast::BuiltInType &returnType,
                      const std::vector<ast::BuiltInType> &paramTypes);

        void visit(ast::Num &node) override;

        void visit(ast::NumB &node) override;

        void visit(ast::String &node) override;

        void visit(ast::Bool &node) override;

        void visit(ast::ID &node) override;

        void visit(ast::BinOp &node) override;

        void visit(ast::RelOp &node) override;

        void visit(ast::Not &node) override;

        void visit(ast::And &node) override;

        void visit(ast::Or &node) override;

        //void visit(ast::Type &node) override;

        void visit(ast::ArrayType &node) override;

        void visit(ast::PrimitiveType &node) override;

        void visit(ast::ArrayDereference &node) override;

        void visit(ast::ArrayAssign &node) override;

        void visit(ast::Cast &node) override;

        void visit(ast::ExpList &node) override;

        void visit(ast::Call &node) override;

        void visit(ast::Statements &node) override;

        void visit(ast::Break &node) override;

        void visit(ast::Continue &node) override;

        void visit(ast::Return &node) override;

        void visit(ast::If &node) override;

        void visit(ast::While &node) override;

        void visit(ast::VarDecl &node) override;

        void visit(ast::Assign &node) override;

        void visit(ast::Formal &node) override;

        void visit(ast::Formals &node) override;

        void visit(ast::FuncDecl &node) override;

        void visit(ast::Funcs &node) override;
    };
}

#endif //OUTPUT_HPP
