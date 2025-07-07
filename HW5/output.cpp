#include "output.hpp"
#include <iostream>
#include <algorithm>

namespace output {
    /* Helper functions */


    bool is_number(const std::shared_ptr<ast::Exp>& exp) {
        return exp->type == ast::BuiltInType::INT || exp->type == ast::BuiltInType::BYTE;
    }

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

    static std::string toStringCapital(ast::BuiltInType type) {
        switch (type) {
            case ast::BuiltInType::INT:
                return "INT";
            case ast::BuiltInType::BOOL:
                return "BOOL";
            case ast::BuiltInType::BYTE:
                return "BYTE";
            case ast::BuiltInType::VOID:
                return "VOID";
            case ast::BuiltInType::STRING:
                return "STRING";
            default:
                return "UNKNOWN";
        }
    }

    // Helper function to find the type of virtual 'Type' classs object.
    ast::BuiltInType find_type(const std::shared_ptr<ast::Type> t) {
        if (auto prim = std::dynamic_pointer_cast<ast::PrimitiveType>(t))
        {
            return prim->type;
        }
        else if (auto arr = std::dynamic_pointer_cast<ast::ArrayType>(t))
        {
            return arr->type;
        }
        else
        {
            // The program should not get to this point because every 'Type' object is rather 'PrimitivaType' or 'ArrayType'.
            return ast::BuiltInType::NONE;
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
        std::cout << "line " << lineno << ": invalid assignment to array " << id_arr << std::endl;
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

    void ScopePrinter::emitArr(const std::string &id, const ast::BuiltInType &type, int length , int offset ) {
        buffer << indent() << id << "[" << length << "]" << " " << toString(type) << " " << offset <<  std::endl;
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

    /* CodeBuffer class */

    CodeBuffer::CodeBuffer() : labelCount(0), varCount(0), stringCount(0), stack_sized(false) {}

    std::string CodeBuffer::freshLabel() {
        if(stack_sized)
            return "%label_" + std::to_string(labelCount++);
        return "";
    }

    std::string CodeBuffer::freshVar() {
        if(stack_sized)
            return "%t" + std::to_string(varCount++);
        return "";
    }

    std::string CodeBuffer::emitString(const std::string &str) {
        std::string var = "@.str" + std::to_string(stringCount++);
        globalsBuffer << var << " = constant [" << str.length() + 1 << " x i8] c\"" << str << "\\00\"";
        return var;
    }

    std::string CodeBuffer::convert_to_arg(const std::string &const_str, const std::string &str) {
        // Create a fresh variable for the result of getelementptr
        std::string ptr = freshVar();

        // Length of the string, including null terminator
        int length = str.length() + 1;

        // Emit the getelementptr instruction
        *this << ptr << " = getelementptr [" << length << " x i8], [" << length << " x i8]* "
              << const_str << ", i32 0, i32 0" << std::endl;

        return ptr;
    }

    void CodeBuffer::emitZeroInitStack(const std::string& stack_alloc) {
        std::string stack_ptr = freshVar();
        std::string index_ptr = freshVar();
        std::string loop_i = freshVar();
        std::string cond = freshVar();
        std::string elem_ptr = freshVar();
        std::string i_next = freshVar();

        std::string loop_cond_label = freshLabel().erase(0,1);

        std::string loop_body_label = freshLabel().erase(0,1);

        std::string loop_end_label = freshLabel().erase(0,1);


        *this << stack_ptr << " = getelementptr i32, i32* " << stack_alloc << ", i32 0\n";
        *this << index_ptr << " = alloca i32\n";
        *this << "store i32 0, i32* " << index_ptr << "\n";
        *this << "br label %" << loop_cond_label << "\n";

        *this << loop_cond_label << ":\n";
        *this << loop_i << " = load i32, i32* " << index_ptr << "\n";
        *this << cond << " = icmp slt i32 " << loop_i << ", %stacksize\n";
        *this << "br i1 " << cond << ", label %" << loop_body_label << ", label %" << loop_end_label << "\n";

        *this << loop_body_label << ":\n";
        *this << elem_ptr << " = getelementptr i32, i32* " << stack_ptr << ", i32 " << loop_i << "\n";
        *this << "store i32 0, i32* " << elem_ptr << "\n";
        *this << i_next << " = add i32 " << loop_i << ", 1\n";
        *this << "store i32 " << i_next << ", i32* " << index_ptr << "\n";
        *this << "br label %" << loop_cond_label << "\n";

        *this << loop_end_label << ":\n";
    }

    void CodeBuffer::emit(const std::string &str) {
        buffer << str << std::endl;
    }

    void CodeBuffer::emitLabel(const std::string &label) {
        buffer << label.substr(1) << ":" << std::endl;
    }

    CodeBuffer &CodeBuffer::operator<<(std::ostream &(*manip)(std::ostream &)) {
        if(stack_sized){
            buffer << manip;
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const CodeBuffer &buffer) {
        os << buffer.globalsBuffer.str() << std::endl << buffer.buffer.str();
        return os;
    }


    /* SemanticVisitor implementation */
    SemanticVisitor::SemanticVisitor() : first_run(true), loopDepth(0), max_offset(0) {
        offsets.push(0);
        push_func("print", ast::BuiltInType::VOID, {ast::BuiltInType::STRING});
        push_func("printi", ast::BuiltInType::VOID, {ast::BuiltInType::INT});
    }

    void SemanticVisitor::code_global_funcs() {
        buffer.emit("declare i32 @scanf(i8*, ...)");
        buffer.emit("declare i32 @printf(i8*, ...)");
        buffer.emit("declare void @exit(i32)");
        buffer.emit("@.int_specifier_scan = constant [3 x i8] c\"%d\\00\"");
        buffer.emit("@.int_specifier = constant [4 x i8] c\"%d\\0A\\00\"");
        buffer.emit("@.str_specifier = constant [4 x i8] c\"%s\\0A\\00\"");
        buffer.emit("");
        buffer.emit("define i32 @readi(i32) {");
        buffer.emit("    %ret_val = alloca i32");
        buffer.emit("    %spec_ptr = getelementptr [3 x i8], [3 x i8]* @.int_specifier_scan, i32 0, i32 0");
        buffer.emit("    call i32 (i8*, ...) @scanf(i8* %spec_ptr, i32* %ret_val)");
        buffer.emit("    %val = load i32, i32* %ret_val");
        buffer.emit("    ret i32 %val");
        buffer.emit("}");
        buffer.emit("");
        buffer.emit("define void @printi(i32) {");
        buffer.emit("    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0");
        buffer.emit("    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)");
        buffer.emit("    ret void");
        buffer.emit("}");
        buffer.emit("");
        buffer.emit("define void @print(i8*) {");
        buffer.emit("    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0");
        buffer.emit("    call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)");
        buffer.emit("    ret void");
        buffer.emit("}");
        buffer.emit("");
    }

    std::shared_ptr<SymbolTable> SemanticVisitor::makeTable() {
        return std::make_shared<SymbolTable>();
    }

    // Push variable into the symbol_stack (the Symbol Table).
    void SemanticVisitor::push_var(const std::string& id, const ast::BuiltInType& type, bool isArray, int arrSize) {
        Var_Entry entry = {type, offsets.top(), isArray, arrSize};
        symbol_stack.top()->table[id] = entry;
        if(isArray){
            scopePrinter.emitArr(id, type, arrSize, offsets.top());
            offsets.top() += arrSize;
        }
        else{
            scopePrinter.emitVar(id, type, offsets.top());
            offsets.top()++;
        }
        max_offset = std::max(max_offset, offsets.top());
    }

    // Push variable into the symbol_stack (the Symbol Table).
    void SemanticVisitor::reset_max() {
        max_offset = 0;
    }

    void SemanticVisitor::push_param(const std::string& id, const ast::BuiltInType& type, int neg_offset) {
        Var_Entry entry = {type, neg_offset};
        symbol_stack.top()->table[id] = entry;
        scopePrinter.emitVar(id, type, neg_offset);
    }

    // // asume number exist
    // bool SemanticVisitor::is_number(std::string& name) {
    //     // Iterating through the stack.
    //     std::stack<std::shared_ptr<SymbolTable>> temp_stack = symbol_stack;
    //     while (!temp_stack.empty())
    //     {
    //         // Searching the element in the current symbolTable.
    //         const std::shared_ptr<SymbolTable>& symbolTable = temp_stack.top();
    //         if (symbolTable->table.find(name) != symbolTable->table.end())
    //         {
    //             return symbolTable->table[name].type == ast::BuiltInType::INT || symbolTable->table[name].type  == ast::BuiltInType::BYTE;
    //         }
    //         // Didn't found, countinue to search the element in the stack's symbolTables.
    //         temp_stack.pop();
    //     }
    //     return false;
    // }

    bool SemanticVisitor::search_var(std::string& name) {
        // Iterating through the stack.
        std::stack<std::shared_ptr<SymbolTable>> temp_stack = symbol_stack;
        while (!temp_stack.empty())
        {
            // Searching the element in the current symbolTable.
            const std::shared_ptr<SymbolTable>& symbolTable = temp_stack.top();
            if (symbolTable->table.find(name) != symbolTable->table.end())
            {
                return true;
            }
            // Didn't found, countinue to search the element in the stack's symbolTables.
            temp_stack.pop();
        }
        return false;
    }

    // Returns the type of the variable from the symbol table.
    ast::BuiltInType SemanticVisitor::vars_type(std::string& name) {
        // Iterating through the stack.
        std::stack<std::shared_ptr<SymbolTable>> temp_stack = symbol_stack;
        while (!temp_stack.empty())
        {
            // Searching the element in the current symbolTable.
            const std::shared_ptr<SymbolTable>& symbolTable = temp_stack.top();
            if (symbolTable->table.find(name) != symbolTable->table.end())
            {
                return symbolTable->table[name].type;
            }
            // Didn't found, countinue to search the element in the stack's symbolTables.
            temp_stack.pop();
        }
        return ast::NONE; // shouldnt get here
    }

    // Returns the Var_Entry of the variable from the symbol table.
    Var_Entry SemanticVisitor::vars_info(std::string& name) {
        // Iterating through the stack.
        std::stack<std::shared_ptr<SymbolTable>> temp_stack = symbol_stack;
        while (!temp_stack.empty())
        {
            // Searching the element in the current symbolTable.
            const std::shared_ptr<SymbolTable>& symbolTable = temp_stack.top();
            if (symbolTable->table.find(name) != symbolTable->table.end())
            {
                return symbolTable->table[name];
            }
            // Didn't found, countinue to search the element in the stack's symbolTables.
            temp_stack.pop();
        }
        return Var_Entry(); // shouldnt get here
    }


    // Return reather or not the variable is an array.
    // If the variable is not found, return false.
    bool SemanticVisitor::isArr(std::string& name){
        // Implementation is very similar to 'vars_type' function.

        std::stack<std::shared_ptr<SymbolTable>> temp_stack = symbol_stack;
        while (!temp_stack.empty())
        {
            // Searching the element in the current symbolTable.
            const std::shared_ptr<SymbolTable>& symbolTable = temp_stack.top();
            if (symbolTable->table.find(name) != symbolTable->table.end())
            {
                return symbolTable->table[name].isArray;
            }
            // Didn't found, countinue to search the element in the stack's symbolTables.
            temp_stack.pop();
        }
        return false; // shouldnt get here
    }

    void SemanticVisitor::push_func(const std::string& id, const ast::BuiltInType& returnType,
                                    const std::vector<ast::BuiltInType>& paramTypes) {
        func_table[id] = {paramTypes, returnType, 0};
        scopePrinter.emitFunc(id, returnType, paramTypes);
    }

    ast::BuiltInType SemanticVisitor::func_return_type(std::string& name) {
        if (func_table.find(name) != func_table.end())
            return func_table[name].returnType;
        return ast::BuiltInType::NONE;
    }

    bool SemanticVisitor::search_func(std::string& name) {
        if (func_table.find(name) != func_table.end())
            return true;
        return false;
    }

    void SemanticVisitor::visit(ast::Num& node) {
        node.reg = std::to_string(node.value);
        return;
    }

    void SemanticVisitor::visit(ast::NumB& node) {
        // Check that byte value is smaller or equal to 255.
        if(node.value > 255){
            errorByteTooLarge(node.line, node.value);
        }
        node.reg = std::to_string(node.value);
        return;
    }

    void SemanticVisitor::visit(ast::String& node) {
        if(!buffer.stack_sized)
        {
            node.reg = buffer.emitString(node.value);
        } else {
            node.reg = buffer.convert_to_arg(node.reg, node.value);
        }

        return;
    }

    void SemanticVisitor::visit(ast::Bool& node) {
        node.reg = node.value ? "1" : "0";
        return;
    }

    void SemanticVisitor::visit(ast::ID& node) {
        // Search the ID in the symbol table. Update its type.
        // Note: ID can define both variables and functions.
        // Therefore we need to search both tables.
        // If we didnot find the variable in the tables - how can we know if it is a function or a variable?
        // We will know by the SemanticVisitor.first_run.
        if(search_var(node.value)){
            node.type = vars_type(node.value);
        }
        else if(search_func(node.value)){
            node.type = func_return_type(node.value);
        }
        else{ // If the ID is not in the symbol table, then return an error of undefined variable.
            errorUndef(node.line, node.value);
        }

        int stack_offset = vars_info(node.value).offset;
        std::string element_ptr_reg = buffer.freshVar();
        buffer << element_ptr_reg << " = getelementptr i32, i32* %stack, i32 " << stack_offset << std::endl;

        if(isArr(node.value))
        {
            node.reg = element_ptr_reg;
        } else if(node.type == ast::BOOL) {
            std::string temp_reg = buffer.freshVar();      // for i32 load
            node.reg = buffer.freshVar();                  // for final i1 value
            buffer << temp_reg << " = load i32, i32* " << element_ptr_reg << "\n";
            buffer << node.reg << " = icmp ne i32 " << temp_reg << ", 0\n";
        } else {
            node.reg = buffer.freshVar();
            buffer << node.reg << " = load i32, i32* " << element_ptr_reg << std::endl;
        }
        return;
    }

    void SemanticVisitor::visit(ast::BinOp& node) {
        node.left->accept(*this);
        if (!is_number(node.left))
            errorMismatch(node.line);

        node.right->accept(*this);
        if (!is_number(node.right))
            errorMismatch(node.line);


        if (node.left->type == ast::BuiltInType::INT || node.right->type == ast::BuiltInType::INT)
        {
            node.type = ast::BuiltInType::INT;
        }
        else
        {
            node.type = ast::BuiltInType::BYTE;
        }

        std::string l_reg = node.left->reg;
        std::string r_reg = node.right->reg;
        std::string op;

        switch (node.op) {
            case ast::ADD:
                op = "add"; break;
            case ast::SUB:
                op = "sub"; break;
            case ast::MUL:
                op = "mul"; break;
            case ast::DIV:
                op = node.type == ast::BuiltInType::INT ? "sdiv" : "udiv"; break;
        }

        node.reg = buffer.freshVar();
        buffer << node.reg << " = "  << op << " i32 " << l_reg << ", "<< r_reg << std::endl;
    }

    void SemanticVisitor::visit(ast::RelOp& node) {
        node.left->accept(*this);
        if (!is_number(node.left))
            errorMismatch(node.line);

        node.right->accept(*this);
        if (!is_number(node.right))
            errorMismatch(node.line);

        std::string l_reg = node.left->reg;
        std::string r_reg = node.right->reg;
        std::string relop;

        switch (node.op) {
            case ast::EQ:
                relop = "eq"; break;
            case ast::NE:
                relop = "ne"; break;
            case ast::LT:
                relop = "slt"; break;
            case ast::GT:
                relop = "sgt"; break;
            case ast::LE:
                relop = "sle"; break;
            case ast::GE:
                relop = "sge"; break;
        }

        node.reg = buffer.freshVar();
        buffer << node.reg << " = icmp " << relop << " i32 " << l_reg << ", " << r_reg << std::endl;
    }

    void SemanticVisitor::visit(ast::PrimitiveType& node) {
        // Dont do nothing.
        return;
    }

    void SemanticVisitor::visit(ast::ArrayType& node) {
        // Update node.length->value
        node.length->accept(*this);
        // If node.length is not INT return mismatch error.
        if(node.length->type != ast::BuiltInType::INT){
            errorMismatch(node.line);
        }

        return;
    }

    void SemanticVisitor::visit(ast::ArrayDereference& node) {
        // Check if ID is an array. If not, return type mismatch.
        if(!isArr(node.id->value) || !is_number(node.index)){
            errorMismatch(node.line);
        }
        node.id->accept(*this);
        node.index->accept(*this);
        node.type = node.id->type;

        int array_index = 0;
        if(auto index = std::dynamic_pointer_cast<ast::Num>(node.index)){
            array_index = index->value;
        }
        else if(auto index = std::dynamic_pointer_cast<ast::NumB>(node.index)){
            array_index = index->value;
        }
        else{
            errorMismatch(node.line);
        }

        std::string array_ptr_reg = node.id->reg;
        std::string element_ptr_reg = buffer.freshVar();
        buffer << element_ptr_reg << " = getelementptr i32, i32* "<< array_ptr_reg <<", i32 " << array_index << std::endl;

        node.reg = buffer.freshVar();
        buffer << node.reg << " = load i32, i32* " << element_ptr_reg << std::endl;
    }

    void SemanticVisitor::visit(ast::Cast& node) {
        node.exp->accept(*this);

        node.target_type->accept(*this);
        if (!is_number(node.exp) || (node.target_type->type != ast::BuiltInType::INT && node.target_type->type !=
            ast::BuiltInType::BYTE))
        {
            errorMismatch(node.line);
        }
    }

    void SemanticVisitor::visit(ast::Not& node) {
        node.exp->accept(*this);
        if (node.exp->type != ast::BuiltInType::BOOL)
            errorMismatch(node.line);

        node.reg = buffer.freshVar();
        buffer << node.reg << " = xor i1 0, " << node.exp->reg << std::endl;
    }

    void SemanticVisitor::visit(ast::And& node) {
        node.left->accept(*this);
        if (node.left->type != ast::BuiltInType::BOOL)
            errorMismatch(node.line);

        node.right->accept(*this);
        if (node.right->type != ast::BuiltInType::BOOL)
            errorMismatch(node.line);

        node.reg = buffer.freshVar();
        buffer << node.reg << " = and i1 " << node.left->reg << ", " << node.right->reg << std::endl;
    }

    void SemanticVisitor::visit(ast::Or& node) {
        node.left->accept(*this);
        if (node.left->type != ast::BuiltInType::BOOL)
            errorMismatch(node.line);

        node.right->accept(*this);
        if (node.right->type != ast::BuiltInType::BOOL)
            errorMismatch(node.line);

        node.reg = buffer.freshVar();
        buffer << node.reg << " = or i1 " << node.left->reg << ", " << node.right->reg << std::endl;
    }

    void SemanticVisitor::visit(ast::ExpList& node) {
        for (auto it = node.exps.rbegin(); it != node.exps.rend(); ++it)
        {
            (*it)->accept(*this);
        }
    }

    void SemanticVisitor::visit(ast::Call& node) {
        if (!search_func(node.func_id->value))
            errorUndefFunc(node.line, node.func_id->value);

        if (search_var(node.func_id->value))
            errorDefAsVar(node.line, node.func_id->value);

        node.func_id->accept(*this);
        node.type = func_table[node.func_id->value].returnType;

        std::vector<std::string> expected_param;
        for (ast::BuiltInType type : func_table[node.func_id->value].paramTypes)
        {
            expected_param.push_back(toStringCapital(type));
        }

        // wrong number of arguments pass to function
        if (expected_param.size() != node.args->exps.size())
            errorPrototypeMismatch(node.line, node.func_id->value, expected_param);

        // check if passed argument type match expected types
        node.args->accept(*this);
        int i = 0;
        for (std::shared_ptr<ast::Exp> arg : node.args->exps)
        {
            // Check first if the given parametere is an array.
            if(auto arg_id = std::dynamic_pointer_cast<ast::ID>(arg)){
                if(isArr(arg_id->value)){
                    errorPrototypeMismatch(node.line, arg_id->value, expected_param);
                }
            }
            else if(arg->type == ast::BuiltInType::BYTE && func_table[node.func_id->value].paramTypes[i] == ast::BuiltInType::INT){ // Then check if the parameters is make a cast from byte to int, which is acceptable.
                // Don't do anything.
            }
            else if (arg->type != func_table[node.func_id->value].paramTypes[i]){ // Then check if the types are differenet.
                errorPrototypeMismatch(node.line, node.func_id->value, expected_param);
            }
            i++;
        }

        node.reg = buffer.freshVar();
        std::string return_type = node.type == ast::VOID ? "void" : "i32";
        std::string func_name = node.func_id->value;
        std::string params = "";
        // Arguments
        for (std::shared_ptr<ast::Exp> arg : node.args->exps) {
            std::string arg_reg = arg->reg;
            if (func_name == "print") {
                params += "i8* " + arg_reg;
            }
               else
            {
                params += "i32 " + arg_reg;
            }
            // Just fix this line:
            if (arg != node.args->exps.back())
                params += ", ";
        }
        if(node.type == ast::VOID)
        {
            buffer << "call " << return_type << "@" << func_name << "(" << params << ")" << std::endl;
        } else{
            buffer << node.reg << " = call " << return_type << "@" << func_name << "(" << params << ")" << std::endl;
        }
    }

    void SemanticVisitor::visit(ast::Statements& node) {
        // Every statements starts and end with '{' and '}'.
        // We need to open a new scope only if we are outside of a function.
        if(!node.insideFunction){
            scopePrinter.beginScope();
        }
        for (auto it = node.statements.begin(); it != node.statements.end(); ++it)
        {
            (*it)->accept(*this);
            if(auto ret_statement = std::dynamic_pointer_cast<ast::Return>(*it)){
                if(node.returnType != ret_statement->exp->type && // The return types must be equal, or int and byte.
                    !(node.returnType == ast::INT && ret_statement->exp->type == ast::BYTE)){
                        errorMismatch(ret_statement->line);
                }
            }
        }
        if(!node.insideFunction){
            scopePrinter.endScope();
        }
    }

    void SemanticVisitor::visit(ast::Break& node) {
        if (loopDepth == 0)
            errorUnexpectedBreak(node.line);
        std::string end_loop = loop_end_labels.top();
        buffer << "br label " << end_loop << std::endl;
        return;
    }

    void SemanticVisitor::visit(ast::Continue& node) {
        if (loopDepth == 0)
            errorUnexpectedContinue(node.line);
        std::string cond_loop = loop_cond_labels.top();
        buffer << "br label " << cond_loop << std::endl;
        return;
    }

    void SemanticVisitor::visit(ast::Return& node) {
        if (!node.exp)
        {
            buffer << "ret void" << std::endl;
            return;
        }

        node.exp->accept(*this);
        buffer << "ret i32 " << node.exp->reg << std::endl;

    }

    void SemanticVisitor::visit(ast::If& node) {
        node.condition->accept(*this);

        std::string condition_reg = node.condition->reg;
        std::string label_01 = buffer.freshLabel();
        std::string label_01_name = label_01;
        label_01_name.erase(0,1);
        std::string label_02 = buffer.freshLabel();
        std::string label_02_name = label_02;
        label_02_name.erase(0,1);
        std::string label_03 = buffer.freshLabel();
        std::string label_03_name = label_03;
        label_03_name.erase(0,1);
        buffer << "br i1 " << condition_reg << ", label " << label_01 << ", label " << label_02 << std::endl;
        buffer << label_01_name << ":" << std::endl;

        // create a new scope for the ‘if’.
        scopePrinter.beginScope();
        node.then->accept(*this);
        scopePrinter.endScope();

        buffer << "br label " << label_03 << std::endl;
        buffer << label_02_name << ":" << std::endl;

        // Also check if 'else' creates a new block.
        if (node.otherwise) {
            scopePrinter.beginScope();
            node.otherwise->accept(*this);
            scopePrinter.endScope();
        }

        buffer << "br label " << label_03 << std::endl;
        buffer << label_03_name << ":" << std::endl;
    }

    void SemanticVisitor::visit(ast::While& node) {
        std::string label_01 = buffer.freshLabel();
        std::string label_01_name = label_01;
        label_01_name.erase(0,1);

        std::string label_02 = buffer.freshLabel();
        std::string label_02_name = label_02;
        label_02_name.erase(0,1);

        std::string label_03 = buffer.freshLabel();
        std::string label_03_name = label_03;
        label_03_name.erase(0,1);
        
        buffer << "br label " << label_01 << std::endl;
        buffer << label_01_name << ":" << std::endl;
        node.condition->accept(*this);
        std::string condition_reg = node.condition->reg;
        buffer << "br i1 " << condition_reg << ", label " << label_02 << ", label " << label_03 << std::endl;
        buffer << label_02_name << ":" << std::endl;
        
        // open the loop scope.
        scopePrinter.beginScope();
        loopDepth++;
        loop_cond_labels.push(label_02);
        loop_end_labels.push(label_03);
        node.body->accept(*this);
        loopDepth--;
        scopePrinter.endScope();

        buffer << "br label " << label_01 << std::endl;
        buffer << label_03_name << ":" << std::endl;
    }

    // Updated from the HW3 function in the following way:
    //      1) If there is an expression:
    //              then:
    //                   The expression is already stored in a register.
    //                   No code generation needed.
    //              Otherwise:
    //                   There is no allocated register for this new variable. Create a new register with default value.
    //                   Create code that will initialize this register.
    //      2) Create code that will put that variable in the call stack. The offset in the stack will be the offset from the symbol table var entry.
    void SemanticVisitor::visit(ast::VarDecl& node) {
        if (search_var(node.id->value))
            errorDef(node.line, node.id->value);

        if (search_func(node.id->value))
            errorDefAsFunc(node.line, node.id->value);

        ast::BuiltInType node_type = find_type(node.type);

        int arr_length = -1;
        if (auto arr = std::dynamic_pointer_cast<ast::ArrayType>(node.type)){
            if(auto num = std::dynamic_pointer_cast<ast::Num>(arr->length)){ // if length is num
                arr_length = num->value;
            }
            else if(auto numB = std::dynamic_pointer_cast<ast::NumB>(arr->length)){
                arr_length = numB->value;
            }
            push_var(node.id->value, node_type, true, arr_length);
        }
        else{
            push_var(node.id->value, node_type, false, -1);
        }
        node.id->accept(*this);
        node.type->accept(*this);

        if (node.init_exp) {
            node.init_exp->accept(*this);
            // Check for type mismatch!
            if (find_type(node.type) != node.init_exp->type) {
                errorMismatch(node.line);
            } else if (auto exp_id = std::dynamic_pointer_cast<ast::ID>(node.init_exp)) { // Check if RHS is an array.
                if (this->isArr(exp_id->value)) {
                    errorMismatch(node.line);
                }
            }

            // We have an intialization expression, therefore we do not need to create a new register!
            // What we will do is pass the register to the id of the new node. 
            // Also, we will pass this value to the call stack.
            node.reg = node.init_exp->reg;

            // Generated code is as followes:
            //      1) Create temporary register for stack ptr.
            //      2) Store node.reg value in the stack, use the stack ptr from part (1).
            std::string tmp_stack_pointer = buffer.freshVar();
            int node_stack_offset = vars_info(node.id->value).offset;
            buffer << tmp_stack_pointer << " = getelementptr i32, i32* %stack, i32 " << node_stack_offset << std::endl;
            buffer << "store i32 " << node.reg << ", i32* " << tmp_stack_pointer << std::endl;
        }
    }

    void SemanticVisitor::visit(ast::Assign& node) {
        if (!search_var(node.id->value))
            errorUndef(node.line, node.id->value);

        if (search_func(node.id->value))
            errorDefAsFunc(node.line, node.id->value);

        node.id->accept(*this);
        node.id->type = vars_type(node.id->value);

        if(this->isArr(node.id->value)){
            // If the ID is an array, then we would not accept the assignment.
            ErrorInvalidAssignArray(node.line, node.id->value);
        }

        node.exp->accept(*this);
        // Check if the RHS of the assignment is an array id.
        if(auto exp_id = std::dynamic_pointer_cast<ast::ID>(node.exp)){
            if(this->isArr(exp_id->value)){
                errorMismatch(node.line);
            }
        }

        // Generate code:
        // node.exp value is stored in node.exp->reg. We would like to put that value in the stack, with id offset.
        node.reg = node.exp->reg; 
        std::string stack_ptr = buffer.freshVar();
        int var_offset = vars_info(node.id->value).offset;
        buffer << stack_ptr << " = getelementptr i32, i32* %stack, i32 " << var_offset << std::endl;
        buffer << "store i32 " << node.reg << ", i32* " << stack_ptr << std::endl; 
        
        if (node.id->type == node.exp->type)
            return;
        if (node.id->type == ast::INT && node.exp->type == ast::BYTE)
            return;

        errorMismatch(node.line);
    }

    void SemanticVisitor::visit(ast::ArrayAssign& node) {
        // same undef/def checks as for Assign
        if (!search_var(node.id->value))
            errorUndef(node.line, node.id->value);
        if (search_func(node.id->value))
            errorDefAsFunc(node.line, node.id->value);

        node.index->accept(*this);
        if (!is_number(node.index))
            errorMismatch(node.line);

        // 2) look up the array’s element type
        ast::BuiltInType elemType = vars_type(node.id->value);

        // 3) check the LHS
        if(!isArr(node.id->value)){
            errorMismatch(node.line);
        }

        // 4) check the RHS
        node.exp->accept(*this);
        if (node.exp->type == elemType || (elemType == ast::INT && node.exp->type == ast::BYTE)){
            if(auto exp_id = std::dynamic_pointer_cast<ast::ID>(node.exp)){ // Check if RHS is an array.
                if(this->isArr(exp_id->value)){
                    errorMismatch(node.line);
                }
            }

            // Generate code:
            // node.exp value is stored in node.exp->reg. We would like to put that value in the stack, with id offset.
            node.reg = node.exp->reg; 
            std::string array_ptr = buffer.freshVar(); // A pointer to the beginning of the array.
            std::string array_index_ptr = buffer.freshVar(); // A pointer to the actual variable in the array.
            int var_offset = vars_info(node.id->value).offset;
            buffer << array_ptr << " = getelementptr i32, i32* %stack, i32 " << var_offset << std::endl;
            buffer << array_index_ptr << " = getelementptr i32, i32* " << array_ptr << ", i32 " << node.index->reg << std::endl;
            buffer << "store i32 " << node.reg << ", i32* " << array_index_ptr << std::endl; 

            return;
        }

            // any other case is a type mismatch
        errorMismatch(node.line);
    }

    void SemanticVisitor::visit(ast::Formal& node) {
        node.id->accept(*this);
        node.type->accept(*this);
    }

    void SemanticVisitor::visit(ast::Formals& node) {
        for (auto it = node.formals.rbegin(); it != node.formals.rend(); ++it)
        {
            (*it)->accept(*this);
        }
    }

    void SemanticVisitor::visit(ast::FuncDecl& node) {
        if (first_run)
        {
            if (func_table.find(node.id->value) != func_table.end())
            {
                errorDef(node.line, node.id->value);
            }

            std::vector<ast::BuiltInType> paramTypes;
            for (const auto& formal : node.formals->formals)
            {
                paramTypes.push_back(find_type(formal->type));
            }
            push_func(node.id->value,find_type(node.return_type), paramTypes);
            return;
        }

        std::shared_ptr<SymbolTable> sym_t = makeTable();
        scopePrinter.beginScope();
        symbol_stack.push(sym_t);
        offsets.push(offsets.top());
        int i = -1;
        for (std::shared_ptr<ast::Formal>& param : node.formals->formals)
        {
            push_param(param->id->value, find_type(param->type), i);
            i--;
        }

        // We do not want the next few lines to print anything.
        bool real_stack_sized_val = buffer.stack_sized;
        buffer.stack_sized = false;

        node.id->accept(*this);
        node.return_type->accept(*this);
        node.formals->accept(*this);
        node.body->returnType = find_type(node.return_type);
        node.body->insideFunction = true;

        // Return to printing
        buffer.stack_sized = real_stack_sized_val;
        if(buffer.stack_sized)
        {
            std::string func_name = node.id->value;
            std::string return_type_name = "i32";
            if(find_type(node.return_type) == ast::BuiltInType::VOID){
                return_type_name = "void";
            }

            // Put parameters in function signature.
            int param_count = node.formals->formals.size(); // Counter to help us check if we are in the last element.
            int param_index = 0;
            std::string fresh_name;
            buffer << "define " << return_type_name << " @" << func_name << "(";
            for(std::shared_ptr<ast::Formal>& param : node.formals->formals){
                param->reg = buffer.freshVar();
                if(isArr(param->id->value)){
                    buffer << "i32* " << param->reg;
                }
                else{
                    buffer << "i32 " << param->reg;
                }
                if(param_index != param_count - 1){
                    buffer << ", ";
                }
                param_index++;
            }
            buffer << ") {" << std::endl;
            int num_of_parameters = (node.formals->formals).size();
            int stack_size = func_table[node.id->value].max_offset + num_of_parameters;
            buffer << "%stacksize = add i32 0, " << std::to_string(stack_size) << std::endl;
            buffer << "%stack_alloc = alloca i32, i32 %stacksize" << std::endl;
            buffer.emitZeroInitStack();
            // This is a pointer to index 0 of the stack. We allocated memory for the negative indeces.
            buffer << "%stack = getelementptr i32, i32* %stack_alloc, i32 " << num_of_parameters << std::endl;
            
            // Push parameters to the stack.
            for (std::shared_ptr<ast::Formal>& param : node.formals->formals)
            {
                // Insert this register value to the stackat it's offset.
                std::string tmp_stack_pointer = buffer.freshVar();
                int node_stack_offset = vars_info(param->id->value).offset;
                buffer << tmp_stack_pointer << " = getelementptr i32, i32* %stack, i32 " << node_stack_offset << std::endl;
                buffer << "store i32 " << param->reg << ", i32* " << tmp_stack_pointer << std::endl;
            }

            node.body->accept(*this);

            // Check if the last command is ret -> if not, add a return statement.
            if(! std::dynamic_pointer_cast<ast::Return>((node.body->statements).back())){
                if(return_type_name == "i32"){
                    buffer << "ret i32 0" << std::endl;
                }
                else{
                    buffer << "ret void" << std::endl;
                }
            }

            buffer << "}" << std::endl;
            buffer << std::endl;
        }
        else{
            node.body->accept(*this);
        }

        if(!buffer.stack_sized){
            func_table[node.id->value].max_offset = max_offset;
            reset_max();
        }

        offsets.pop();
        symbol_stack.pop();
        scopePrinter.endScope();
    }

    void SemanticVisitor::visit(ast::Funcs& node) {
        if(!first_run){
         // must have exactly one void main() with no parameters
             auto it = func_table.find("main");
             if (it == func_table.end()
                 || it->second.returnType != ast::BuiltInType::VOID
                 || !it->second.paramTypes.empty())
                  {
                      errorMainMissing();
                  }
        }
        for (auto& f : node.funcs) {
            // In first_run mode your Func-visitor should only push the signature
            f->accept(*this);
        }
        if(!first_run)
            buffer.stack_sized = true;
    }
}
