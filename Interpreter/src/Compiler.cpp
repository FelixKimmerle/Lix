#include "Compiler.hpp"

#include <iostream>
#include <sstream>

Compiler::Compiler(Logger *p_Logger, Lix_Func function, LixDatatype return_type) : had_error(false), logger(p_Logger), function(function), return_type(return_type)
{
}
Compiler::Compiler(Logger *p_Logger, LixDatatype return_type) : had_error(false), logger(p_Logger), function(new ObjFunction("main", 0)), return_type(return_type)
{
}

Chunk *Compiler::currentChunk()
{
    return function->getChunk();
}

Chunk::OpCode Compiler::cast(LixDatatype p_From, LixDatatype p_To)
{
    uint8_t opcode = (uint8_t)Chunk::OpCode::OP_CAST_BYTE_SHORTINT + (uint8_t)p_From * 5U + (uint8_t)p_To - (p_To >= p_From ? 1 : 0);
    return (Chunk::OpCode)opcode;
}

void Compiler::pop_one(bool moditernstack)
{
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_POP_BYTE + (uint8_t)m_Stack.back());
    if (moditernstack)
    {
        m_Stack.pop_back();
    }
}

void Compiler::pop_stack(unsigned int n)
{
    unsigned int bytes = 0;
    for (size_t i = 0; i < n; i++)
    {
        bytes += getSize(m_Stack.back());
        m_Stack.pop_back();
    }
    if (bytes != 0)
    {
        currentChunk()->write(Chunk::OpCode::OP_POP);
        currentChunk()->write(bytes);
    }
}

uint8_t Compiler::stack_size(unsigned int n)
{
    uint8_t bytes = 0;
    for (size_t i = 0; i < n; i++)
    {
        bytes += getSize(m_Stack[m_Stack.size() - n - 1]);
    }
    return bytes;
}

void Compiler::push_zero(LixDatatype m_Type)
{
    if (m_Type == LixDatatype::LD_Bool)
    {
        currentChunk()->write(Chunk::OpCode::OP_FALSE);
    }
    else
    {
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_ZERO_BYTE + (uint8_t)m_Type);
    }
    m_Stack.push_back(m_Type);
}

void Compiler::error(TokenPosition position, const std::string &message)
{
    had_error = true;
    std::stringstream ss;
    ss << position;
    logger->log("Error at line: " + ss.str() + ". " + message, Logger::Error);
}

bool Compiler::hadError()
{
    return had_error;
}

void Compiler::add_var(Variable variable)
{
    for (auto var = m_Variables.rbegin(); var != m_Variables.rend(); ++var)
    {
        if (var->get_depth() < m_uiCurrentDepth)
        {
            break;
        }
        if (variable.get_name() == var->get_name())
        {
            error(var->get_position(), "Variable with the name: \"" + variable.get_name() + "\" already declared in this scope.");
        }
    }
    m_Variables.push_back(variable);
}

unsigned int Compiler::size_of_variables()
{
    unsigned int size = 0;
    for (auto var = m_Variables.rbegin(); var != m_Variables.rend(); ++var)
    {
        size += getSize(var->get_type());
    }
    return size;
}

std::pair<uint32_t, LixDatatype> Compiler::resolve_var(VarExpr *p_pExpr)
{
    unsigned int index = m_Variables.size();
    LixDatatype type;
    bool find = false;
    for (auto var = m_Variables.rbegin(); var != m_Variables.rend(); ++var)
    {
        index--;
        if (p_pExpr->get_name() == var->get_name())
        {
            type = var->get_type();
            find = true;
            break;
        }
    }
    if (find)
    {
        int16_t offset = 0;
        for (size_t i = 0; i < index; i++)
        {
            offset += getSize(m_Variables[i].get_type());
        }
        return std::make_pair(offset, type);
    }
    else
    {
        error(p_pExpr->get_position(), "No variable with name: \"" + p_pExpr->get_name() + "\"");
    }
}

void Compiler::visitBinary(BinaryExpr *p_pExpr)
{

    p_pExpr->get_left()->visit(this);
    LixDatatype leftType = m_Stack.back();
    /*
    if (m_Stack.back() != p_pExpr->resultingType())
    {
        currentChunk()->write(cast(m_Stack.back(), p_pExpr->resultingType()));
        m_Stack.pop_back();
        m_Stack.push_back(p_pExpr->resultingType());
    }
    */
    p_pExpr->get_right()->visit(this);
    LixDatatype rightType = m_Stack.back();

    /*
    if (m_Stack.back() != p_pExpr->resultingType())
    {
        currentChunk()->write(cast(m_Stack.back(), p_pExpr->resultingType()));
        m_Stack.pop_back();
        m_Stack.push_back(p_pExpr->resultingType());
    }
    */

    if (rightType != leftType)
    {
        error(p_pExpr->get_position(), "Type of left operand (" + lixDatatypeToString(leftType) + ") does not match type of right operand (" + lixDatatypeToString(rightType) + ")");
    }

    LixDatatype resultingType = rightType;

    switch (p_pExpr->get_binary_operator())
    {
    case BinaryExpr::BO_ADD:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->get_position(), "Cannot add two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_ADD_BYTE + (uint8_t)resultingType);
        break;
    case BinaryExpr::BO_MUL:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->get_position(), "Cannot multiply two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_MULTIPLY_BYTE + (uint8_t)resultingType);
        break;
    case BinaryExpr::BO_SUB:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->get_position(), "Cannot subtract two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_SUBTRACT_BYTE + (uint8_t)resultingType);
        break;
    case BinaryExpr::BO_DIV:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->get_position(), "Cannot divide two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_DIVIDE_BYTE + (uint8_t)resultingType);
        break;
    }
    m_Stack.pop_back();
}
void Compiler::visitUnary(UnaryExpr *p_pExpr)
{
    p_pExpr->get_expr()->visit(this);
    if (m_Stack.back() == LixDatatype::LD_Bool && p_pExpr->get_unary_operator() == UnaryExpr::UnaryOperator::UO_MINUS)
    {
        error(p_pExpr->get_position(), "Dont use \'-\' to negate bool use \'!\' instead.");
    }
    if (m_Stack.back() < LixDatatype::LD_Bool && p_pExpr->get_unary_operator() == UnaryExpr::UnaryOperator::UO_MINUS)
    {
        error(p_pExpr->get_position(), "Dont use \'!\' to negate numerical values use \'-\' instead.");
    }
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_NEGATE_BYTE + (uint8_t)m_Stack.back());
}
void Compiler::visitGrouping(GroupingExpr *p_pExpr)
{
    p_pExpr->get_expr()->visit(this);
}

void Compiler::visitNumber(NumberExpr<Lix_Byte> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_BYTE);
    uint8_t id = currentChunk()->addConstant<Lix_Byte>(p_pExpr->get_number());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Byte);
}
void Compiler::visitNumber(NumberExpr<Lix_Double> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_DOUBLE);
    uint8_t id = currentChunk()->addConstant<Lix_Double>(p_pExpr->get_number());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Double);
}
void Compiler::visitNumber(NumberExpr<Lix_Float> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_FLOAT);
    uint8_t id = currentChunk()->addConstant<Lix_Float>(p_pExpr->get_number());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Float);
}
void Compiler::visitNumber(NumberExpr<Lix_Int> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_INT);
    uint8_t id = currentChunk()->addConstant<Lix_Int>(p_pExpr->get_number());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Int);
}
void Compiler::visitNumber(NumberExpr<Lix_LongInt> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_LONGINT);
    uint8_t id = currentChunk()->addConstant<Lix_LongInt>(p_pExpr->get_number());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_LongInt);
}
void Compiler::visitNumber(NumberExpr<Lix_ShortInt> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_SHORTINT);
    uint8_t id = currentChunk()->addConstant<Lix_ShortInt>(p_pExpr->get_number());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_ShortInt);
}

void Compiler::visitBoolean(BooleanExpr *p_pExpr)
{
    if (p_pExpr->get_boolean())
    {
        currentChunk()->write(Chunk::OpCode::OP_TRUE);
    }
    else
    {
        currentChunk()->write(Chunk::OpCode::OP_FALSE);
    }

    m_Stack.push_back(LixDatatype::LD_Bool);
}

void Compiler::visitExplicitCast(ExplicitCastExpr *p_pExpr)
{
    p_pExpr->get_expr()->visit(this);
    LixDatatype from = m_Stack.back();
    if (from != p_pExpr->get_type())
    {
        m_Stack.pop_back();
        currentChunk()->write(cast(from, p_pExpr->get_type()));
        m_Stack.push_back(p_pExpr->get_type());
    }
}

void Compiler::visitVar(VarExpr *p_pExpr)
{
    std::pair<uint32_t, LixDatatype> var = resolve_var(p_pExpr);
    uint32_t offset = var.first;
    uint8_t a = offset & 0xFF;
    uint8_t b = offset >> 8;
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_GET_BYTE + (uint8_t)var.second);
    currentChunk()->write(a);
    currentChunk()->write(b);
    m_Stack.push_back(var.second);
}

void Compiler::visitOr(OrExpr *p_pExpr)
{
    p_pExpr->get_left()->visit(this);
    unsigned int elseJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    unsigned int endJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP);
    currentChunk()->patchJump(elseJump);
    pop_one();
    p_pExpr->get_right()->visit(this);
    currentChunk()->patchJump(endJump);
    m_Stack.pop_back();
}
void Compiler::visitAnd(AndExpr *p_pExpr)
{
    p_pExpr->get_left()->visit(this);
    unsigned int endJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    pop_one();
    p_pExpr->get_right()->visit(this);
    currentChunk()->patchJump(endJump);
    m_Stack.pop_back();
}
void Compiler::visitComparison(ComparisonExpr *p_pExpr)
{
    p_pExpr->get_left()->visit(this);
    LixDatatype leftType = m_Stack.back();

    p_pExpr->get_right()->visit(this);
    LixDatatype rightType = m_Stack.back();

    if (rightType != leftType)
    {
        error(p_pExpr->get_position(), "Type of left operand (" + lixDatatypeToString(leftType) + ") does not match type of right operand (" + lixDatatypeToString(rightType) + ")");
    }

    switch (p_pExpr->get_binary_operator())
    {
    case ComparisonExpr::BO_GREATER:
        if (rightType == LixDatatype::LD_Bool)
        {
            //error
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_GREATER_BYTE + (uint8_t)rightType);
        break;
    case ComparisonExpr::BO_LESS:
        if (rightType == LixDatatype::LD_Bool)
        {
            //error
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_LESS_BYTE + (uint8_t)rightType);
        break;
    case ComparisonExpr::BO_GREATER_EQUAL:
        if (rightType == LixDatatype::LD_Bool)
        {
            //error
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_LESS_BYTE + (uint8_t)rightType);
        currentChunk()->write(Chunk::OpCode::OP_NEGATE_BOOL);
        break;
    case ComparisonExpr::BO_LESS_EQUAL:
        if (rightType == LixDatatype::LD_Bool)
        {
            //error
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_GREATER_BYTE + (uint8_t)rightType);
        currentChunk()->write(Chunk::OpCode::OP_NEGATE_BOOL);
        break;
    case ComparisonExpr::BO_EQUAL:
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_EQUAL_BYTE + (uint8_t)rightType);
        break;
    }
    m_Stack.pop_back();
    m_Stack.pop_back();
    m_Stack.push_back(LixDatatype::LD_Bool);
}

void Compiler::visitFuncDecl(FuncDecl *p_pStmt)
{
    unsigned int stack_offset = 0;
    for (auto &&arg : *p_pStmt)
    {
        stack_offset += getSize(arg.first);
    }

    Lix_Func func = new ObjFunction(p_pStmt->get_name(), stack_offset);
    Compiler comp(logger, func, p_pStmt->get_return_type());
    for (auto &&arg : *p_pStmt)
    {
        comp.add_var(Variable(arg.first, arg.second, 0, p_pStmt->get_position()));
    }

    comp.compile(*p_pStmt->get_body());
    func->getChunk()->disassemble(p_pStmt->get_name());

    add_var(Variable(LixDatatype::LD_FUNC, p_pStmt->get_name(), m_uiCurrentDepth, p_pStmt->get_position()));
    m_Stack.push_back(LixDatatype::LD_FUNC);
    currentChunk()->write(Chunk::OpCode::OP_PUSH_FUNC);

    uint8_t id = currentChunk()->addConstant(func);
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_FUNC);
}

void Compiler::visitReturnStmt(ReturnStmt *p_pStmt)
{
    p_pStmt->get_expr()->visit(this);
}

void Compiler::visitPrint(PrintStmt *p_pStmt)
{
    p_pStmt->get_expr()->visit(this);
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_PRINT_BYTE + (uint8_t)m_Stack.back());
    m_Stack.pop_back();
}
void Compiler::visitBlock(BlockStmt *p_pStmt)
{
    m_uiCurrentDepth++;
    for (auto &&item : *p_pStmt)
    {
        item->visit(this);
    }

    m_uiCurrentDepth--;
    unsigned int pops = 0;
    while (m_Variables.size() != 0 && m_Variables.back().get_depth() > m_uiCurrentDepth)
    {
        m_Variables.pop_back();
        pops++;
    }

    pop_stack(pops);
}
void Compiler::visitVar(VarStmt *p_pStmt)
{
    add_var(Variable(p_pStmt->get_type(), p_pStmt->get_name(), m_uiCurrentDepth, p_pStmt->get_position()));
    if (p_pStmt->get_initializer() != nullptr)
    {
        p_pStmt->get_initializer()->visit(this);
        if (m_Stack.back() != p_pStmt->get_type())
        {
            currentChunk()->write(cast(m_Stack.back(), p_pStmt->get_type()));
            m_Stack.pop_back();
            m_Stack.push_back(p_pStmt->get_type());
        }
    }
    else
    {
        push_zero(p_pStmt->get_type());
    }
}

void Compiler::visitIf(IfStmt *p_pStmt)
{
    p_pStmt->get_condition()->visit(this);
    unsigned int thenJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    pop_one();
    p_pStmt->get_then()->visit(this);
    unsigned int elseJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP);
    currentChunk()->patchJump(thenJump);
    pop_one();
    if (p_pStmt->get_else() != nullptr)
    {
        p_pStmt->get_else()->visit(this);
    }
    currentChunk()->patchJump(elseJump);
    m_Stack.pop_back();
}

void Compiler::visitWhile(WhileStmt *p_pStmt)
{
    unsigned int loopStart = currentChunk()->getChunkPos();
    p_pStmt->get_condition()->visit(this);
    unsigned int exitJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    pop_one();
    p_pStmt->get_body()->visit(this);
    currentChunk()->emitLoop(loopStart);
    currentChunk()->patchJump(exitJump);
    pop_one();
    m_Stack.pop_back();
}
void Compiler::visitFor(ForStmt *p_pStmt)
{
    if (p_pStmt->get_initializer() != nullptr)
    {
        p_pStmt->get_initializer()->visit(this);
    }
    unsigned int loopStart = currentChunk()->getChunkPos();
    unsigned int jump = 0;
    if (p_pStmt->get_condition() != nullptr)
    {
        p_pStmt->get_condition()->visit(this);
        jump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
        pop_one();
    }
    p_pStmt->get_body()->visit(this);
    if (p_pStmt->get_increment() != nullptr)
    {
        p_pStmt->get_increment()->visit(this);
        pop_one(true);
    }
    currentChunk()->emitLoop(loopStart);
    if (p_pStmt->get_condition() != nullptr)
    {
        currentChunk()->patchJump(jump);
        pop_one();
        m_Stack.pop_back();
    }
    //popStack(p_pStmt->getPops());
}
void Compiler::visitExprStmt(ExprStmt *p_pStmt)
{
    p_pStmt->get_expr()->visit(this);
    pop_one(true);
}

void Compiler::visitCall(CallExpr *p_pExpr)
{
    //m_Stack.push_back(p_pExpr->)
    for (auto &&expr : *p_pExpr)
    {
        expr->visit(this);
    }
    p_pExpr->get_callee()->visit(this);
    currentChunk()->write(Chunk::OpCode::OP_CALL_FUNC);
    currentChunk()->write(size_of_variables());
    for (auto &&expr : *p_pExpr)
    {
        m_Stack.pop_back();
    }
}

void Compiler::visitAssign(AssignExpr *p_pExpr)
{
    p_pExpr->get_expr()->visit(this);
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_SET_BYTE + (uint8_t)m_Stack.back());
    std::pair<uint32_t, LixDatatype> var = resolve_var(p_pExpr->get_var_expr());
    uint32_t offset = var.first;
    uint8_t a = offset & 0xFF;
    uint8_t b = offset >> 8;
    currentChunk()->write(a);
    currentChunk()->write(b);
}

Lix_Func Compiler::compile(const BlockStmt &block)
{
    m_uiCurrentDepth = 0;
    for (auto &stmt : block)
    {
        stmt->visit(this);
    }
    //popStack(m_Stack.size());
    currentChunk()->write(Chunk::OpCode::OP_RETURN);
    return function;
}