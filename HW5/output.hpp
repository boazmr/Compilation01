#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <vector>
#include <string>
#include <sstream>
#include "visitor.hpp"
#include "nodes.hpp"
#include <map>
#include <stack>

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

        void emitArr(const std::string &id, const ast::BuiltInType &type, int length , int offset );
        
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
        bool isArray = false;
        int arrSize = -1;
        std::string reg;
    };

    struct Func_Entry {
        std::vector<ast::BuiltInType> paramTypes;
        ast::BuiltInType returnType;
    };


    struct SymbolTable{
        std::map<std::string, Var_Entry> table;
    };

    /* CodeBuffer class
     * This class is used to store the generated code.
     * It provides a simple interface to emit code and manage labels and variables.
     */
    class CodeBuffer {
    private:
        std::stringstream globalsBuffer;
        std::stringstream buffer;
        int labelCount;
        int varCount;
        int stringCount;

        friend std::ostream &operator<<(std::ostream &os, const CodeBuffer &buffer);

    public:
        CodeBuffer();

        // Returns a string that represents a label not used before
        // Usage examples:
        //      emitLabel(freshLabel());
        //      buffer << "br label " << freshLabel() << std::endl;
        std::string freshLabel();

        // Returns a string that represents a variable not used before
        // Usage examples:
        //      std::string var = freshVar();
        //      buffer << var << " = icmp eq i32 0, 0" << std::endl;
        std::string freshVar();

        // Emits a label into the buffer
        void emitLabel(const std::string &label);

        // Emits a constant string into the globals section of the code.
        // Returns the name of the constant. For the string of the length n (not including null character), the type is [n+1 x i8]
        // Usage examples:
        //      std::string str = emitString("Hello, World!");
        //      buffer << "call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* " << str << ", i32 0, i32 0))" << std::endl;
        std::string emitString(const std::string &str);

        // Emits a string into the buffer
        void emit(const std::string &str);

        // Template overload for general types
        template<typename T>
        CodeBuffer &operator<<(const T &value) {
            buffer << value;
            return *this;
        }

        // Overload for manipulators (like std::endl)
        CodeBuffer &operator<<(std::ostream &(*manip)(std::ostream &));
    };

    std::ostream &operator<<(std::ostream &os, const CodeBuffer &buffer);

    /* SementicVisitor class
     * This class is used checks scopes and assignment rulles
     */
    class SemanticVisitor : public Visitor {
    private:
        // The symbol table, implementad as a scopes stack.
        std::stack<std::shared_ptr<SymbolTable>> symbol_stack;
        // Stack of scopes offsets.
        std::stack<int> offsets;
        // data struct that saves func
        std::map<std::string, Func_Entry> func_table;


    public:
        ScopePrinter scopePrinter;
        CodeBuffer buffer;
        bool first_run;
        int loopDepth;
        SemanticVisitor();
        std::shared_ptr<SymbolTable> makeTable();
        ast::BuiltInType vars_type(std::string& name);
        Var_Entry vars_info(std::string& name);
        bool search_var(std::string& name);
        bool isArr(std::string& name);
        // bool is_number(std::string& name);
        void push_var(const std::string &id, const ast::BuiltInType &type, bool isArray = false, int arrSize = 0);
        void push_param(const std::string &id, const ast::BuiltInType &type, int neg_offset);

        ast::BuiltInType func_return_type(std::string& name);
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

//    /* CodeGenVisitor class
//     * This class is used to generate code
//     */
//    class CodeGenVisitor : public Visitor {
//    private:
//
//
//    public:
//        CodeBuffer buffer;
//
//        void visit(ast::Num &node) override;
//
//        void visit(ast::NumB &node) override;
//
//        void visit(ast::String &node) override;
//
//        void visit(ast::Bool &node) override;
//
//        void visit(ast::ID &node) override;
//
//        void visit(ast::BinOp &node) override;
//
//        void visit(ast::RelOp &node) override;
//
//        void visit(ast::Not &node) override;
//
//        void visit(ast::And &node) override;
//
//        void visit(ast::Or &node) override;
//
//        //void visit(ast::Type &node) override;
//
//        void visit(ast::ArrayType &node) override;
//
//        void visit(ast::PrimitiveType &node) override;
//
//        void visit(ast::ArrayDereference &node) override;
//
//        void visit(ast::ArrayAssign &node) override;
//
//        void visit(ast::Cast &node) override;
//
//        void visit(ast::ExpList &node) override;
//
//        void visit(ast::Call &node) override;
//
//        void visit(ast::Statements &node) override;
//
//        void visit(ast::Break &node) override;
//
//        void visit(ast::Continue &node) override;
//
//        void visit(ast::Return &node) override;
//
//        void visit(ast::If &node) override;
//
//        void visit(ast::While &node) override;
//
//        void visit(ast::VarDecl &node) override;
//
//        void visit(ast::Assign &node) override;
//
//        void visit(ast::Formal &node) override;
//
//        void visit(ast::Formals &node) override;
//
//        void visit(ast::FuncDecl &node) override;
//
//        void visit(ast::Funcs &node) override;
//    };
}

#endif //OUTPUT_HPP
