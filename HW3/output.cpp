   #include "output.hpp"
#include <iostream>

namespace output {
    /* Helper functions */

    static std::string toString(ast::BuiltInType type) {
        switch (type) {
            case ast::BuiltInType::INT:
                return "int";
            case ast::BuiltInType::BOOL:
                return "bool";
            case ast::BuiltInType::BYTE:
                return "byte";
            case ast::BuiltInType::VOID:
                return "void";
            case ast::BuiltInType::STRING:
                return "string";
            default:
                return "unknown";
        }
    }

    /* Error handling functions */

    void errorLex(int lineno) {
        std::cout << "line " << lineno << ": lexical error\n";
        exit(0);
    }

    void errorSyn(int lineno) {
        std::cout << "line " << lineno << ": syntax error\n";
        exit(0);
    }

    void errorUndef(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " variable " << id << " is not defined" << std::endl;
        exit(0);
    }

    void errorDefAsFunc(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is a function" << std::endl;
        exit(0);
    }

    void errorDefAsVar(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is a variable" << std::endl;
        exit(0);
    }

    void errorDef(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is already defined" << std::endl;
        exit(0);
    }

    void errorUndefFunc(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " function " << id << " is not defined" << std::endl;
        exit(0);
    }

    void errorMismatch(int lineno) {
        std::cout << "line " << lineno << ":" << " type mismatch" << std::endl;
        exit(0);
    }

    void errorPrototypeMismatch(int lineno, const std::string &id, std::vector<std::string> &paramTypes) {
        std::cout << "line " << lineno << ": prototype mismatch, function " << id << " expects parameters (";

        for (int i = 0; i < paramTypes.size(); ++i) {
            std::cout << paramTypes[i];
            if (i != paramTypes.size() - 1)
                std::cout << ",";
        }

        std::cout << ")" << std::endl;
        exit(0);
    }

    void errorUnexpectedBreak(int lineno) {
        std::cout << "line " << lineno << ":" << " unexpected break statement" << std::endl;
        exit(0);
    }

    void errorUnexpectedContinue(int lineno) {
        std::cout << "line " << lineno << ":" << " unexpected continue statement" << std::endl;
        exit(0);
    }

    void errorMainMissing() {
        std::cout << "Program has no 'void main()' function" << std::endl;
        exit(0);
    }

    void errorByteTooLarge(int lineno, const int value) {
        std::cout << "line " << lineno << ": byte value " << value << " out of range" << std::endl;
        exit(0);
    }

    void ErrorInvalidAssignArray(int lineno, const std::string &id_arr) {
        std::cout << "line " << lineno << ": invalid assignment to/from array " << id_arr << std::endl;
        exit(0);
    }

    /* ScopePrinter class */

    ScopePrinter::ScopePrinter() : indentLevel(0) {}

    std::string ScopePrinter::indent() const {
        std::string result;
        for (int i = 0; i < indentLevel; ++i) {
            result += "  ";
        }
        return result;
    }

    void ScopePrinter::beginScope() {
        indentLevel++;
        buffer << indent() << "---begin scope---" << std::endl;
    }

    void ScopePrinter::endScope() {
        buffer << indent() << "---end scope---" << std::endl;
        indentLevel--;
    }

    void ScopePrinter::emitVar(const std::string &id, const ast::BuiltInType &type, int offset) {
        buffer << indent() << id << " " << toString(type) << " " << offset << std::endl;
    }

    void ScopePrinter::emitFunc(const std::string &id, const ast::BuiltInType &returnType,
                                const std::vector<ast::BuiltInType> &paramTypes) {
        globalsBuffer << id << " " << "(";

        for (int i = 0; i < paramTypes.size(); ++i) {
            globalsBuffer << toString(paramTypes[i]);
            if (i != paramTypes.size() - 1)
                globalsBuffer << ",";
        }

        globalsBuffer << ")" << " -> " << toString(returnType) << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const ScopePrinter &printer) {
        os << "---begin global scope---" << std::endl;
        os << printer.globalsBuffer.str();
        os << printer.buffer.str();
        os << "---end global scope---" << std::endl;
        return os;
    }

/* SemanticVisitor implementation */
    SemanticVisitor::SemanticVisitor() : first_run(true) {};

    void SemanticVisitor::push_symbol_table(){
        // TODO
    }
    
    void SemanticVisitor::pop_symbol_table(){
        // TODO
    }

    void SemanticVisitor::visit(ast::Num &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::NumB &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::String &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::Bool &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::ID &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::BinOp &node) {
        node.left->accept(*this);
        node.right->accept(*this);
    }

    void SemanticVisitor::visit(ast::RelOp &node) {
        node.left->accept(*this);
        node.right->accept(*this);
    }

    void SemanticVisitor::visit(ast::PrimitiveType &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::ArrayType &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::ArrayDereference &node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::Cast &node) {
        // TODO:
        // Check if this cast is correct.
    }

    void SemanticVisitor::visit(ast::Not &node) {
        node.exp->accept(*this);
    }

    void SemanticVisitor::visit(ast::And &node) {
        node.left->accept(*this);
        node.right->accept(*this);
    }

    void SemanticVisitor::visit(ast::Or &node) {
        node.left->accept(*this);
        node.right->accept(*this);
    }

    void SemanticVisitor::visit(ast::ExpList &node) {
        for (auto it = node.exps.rbegin(); it != node.exps.rend(); ++it) {
            (*it)->accept(*this);
        }
    }

    void SemanticVisitor::visit(ast::Call &node) {
        node.func_id->accept(*this);
        node.args->accept(*this);
    }

    void SemanticVisitor::visit(ast::Statements &node) {
        for (auto it = node.statements.begin(); it != node.statements.end(); ++it) {
            (*it)->accept(*this);
        }
    }

    void SemanticVisitor::visit(ast::Break &node) {
        print_indented("Break");
    }

    void SemanticVisitor::visit(ast::Continue &node) {
        print_indented("Continue");
    }

    void SemanticVisitor::visit(ast::Return &node) {
        print_indented("Return");

        if (node.exp) {
            enter_last_child();
            node.exp->accept(*this);
            leave_child();
        }
    }

    void SemanticVisitor::visit(ast::If &node) {
        print_indented("If");

        enter_child();
        node.condition->accept(*this);
        leave_child();

        if (node.otherwise) {
            enter_child();
        } else {
            enter_last_child();
        }
        node.then->accept(*this);
        leave_child();

        if (node.otherwise) {
            enter_last_child();
            node.otherwise->accept(*this);
            leave_child();
        }
    }

    void SemanticVisitor::visit(ast::While &node) {
        print_indented("While");

        enter_child();
        node.condition->accept(*this);
        leave_child();

        enter_last_child();
        node.body->accept(*this);
        leave_child();
    }

    void SemanticVisitor::visit(ast::VarDecl &node) {
        print_indented("VarDecl");

        enter_child();
        node.id->accept(*this);
        leave_child();

        if (node.init_exp) {
            enter_child();
        } else {
            enter_last_child();
        }
        node.type->accept(*this);
        leave_child();

        if (node.init_exp) {
            enter_last_child();
            node.init_exp->accept(*this);
            leave_child();
        }
    }

    void SemanticVisitor::visit(ast::Assign &node) {
        print_indented("Assign");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_last_child();
        node.exp->accept(*this);
        leave_child();
    }

    void SemanticVisitor::visit(ast::ArrayAssign &node) {
        print_indented("ArrayAssign");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_child();
        node.index->accept(*this);
        leave_child();

        enter_last_child();
        node.exp->accept(*this);
        leave_child();
    }

    void SemanticVisitor::visit(ast::Formal &node) {
        print_indented("Formal");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_last_child();
        node.type->accept(*this);
        leave_child();
    }

    void SemanticVisitor::visit(ast::Formals &node) {
        print_indented("Formals");

        for (auto it = node.formals.rbegin(); it != node.formals.rend(); ++it) {
            if (it != node.formals.rend() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }

    void SemanticVisitor::visit(ast::FuncDecl &node) {
        print_indented("FuncDecl");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_child();
        node.return_type->accept(*this);
        leave_child();

        enter_child();
        node.formals->accept(*this);
        leave_child();

        enter_last_child();
        node.body->accept(*this);
        leave_child();
    }

    void SemanticVisitor::visit(ast::Funcs &node) {
        print_indented("Funcs");

        for (auto it = node.funcs.begin(); it != node.funcs.end(); ++it) {
            if (it != node.funcs.end() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }
}
