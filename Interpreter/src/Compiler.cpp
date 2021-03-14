#include "Compiler.hpp"
#include <iostream>

Compiler::Compiler(Logger *p_Logger, Lix_Func function, LixDatatype return_type) : m_bHadError(false), m_Logger(p_Logger), function(function), return_type(return_type)
{
}
Compiler::Compiler(Logger *p_Logger, LixDatatype return_type) : m_bHadError(false), m_Logger(p_Logger), function(new ObjFunction("main", 0)), return_type(return_type)
{
}

Compiler::~Compiler()
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

void Compiler::popOne(bool moditernstack)
{
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_POP_BYTE + (uint8_t)m_Stack.back());
    if (moditernstack)
    {
        m_Stack.pop_back();
    }
}

void Compiler::popStack(unsigned int n)
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

void Compiler::pushZero(LixDatatype m_Type)
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

void Compiler::error(unsigned int line, const std::string &message)
{
    m_bHadError = true;
    m_Logger->log("Error at line: " + std::to_string(line) + ". " + message, Logger::Error);
}

bool Compiler::hadError()
{
    return m_bHadError;
}

void Compiler::addVar(Variable variable)
{
    for (auto var = m_Variables.rbegin(); var != m_Variables.rend(); ++var)
    {
        if (var->getDepth() < m_uiCurrentDepth)
        {
            break;
        }
        if (variable.getName() == var->getName())
        {
            error(var->getLine(), "Variable with the name: \"" + variable.getName() + "\" already declared in this scope.");
        }
    }
    m_Variables.push_back(variable);
}

unsigned int Compiler::size_of_variables()
{
    unsigned int size = 0;
    for (auto var = m_Variables.rbegin(); var != m_Variables.rend(); ++var)
    {
        size += getSize(var->getType());
    }
    return size;
}

std::pair<uint32_t, LixDatatype> Compiler::resolveVar(VarExpr *p_pExpr)
{
    unsigned int index = m_Variables.size();
    LixDatatype type;
    bool find = false;
    for (auto var = m_Variables.rbegin(); var != m_Variables.rend(); ++var)
    {
        index--;
        if (p_pExpr->getName() == var->getName())
        {
            type = var->getType();
            find = true;
            break;
        }
    }
    if (find)
    {
        int16_t offset = 0;
        for (size_t i = 0; i < index; i++)
        {
            offset += getSize(m_Variables[i].getType());
        }
        return std::make_pair(offset, type);
    }
    else
    {
        error(p_pExpr->getLine(), "No variable with name: \"" + p_pExpr->getName() + "\"");
    }
}

void Compiler::visitBinary(BinaryExpr *p_pExpr)
{

    p_pExpr->getLeft()->visit(this);
    LixDatatype leftType = m_Stack.back();
    /*
    if (m_Stack.back() != p_pExpr->resultingType())
    {
        currentChunk()->write(cast(m_Stack.back(), p_pExpr->resultingType()));
        m_Stack.pop_back();
        m_Stack.push_back(p_pExpr->resultingType());
    }
    */
    p_pExpr->getRight()->visit(this);
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
        error(p_pExpr->getLine(), "Type of left operand (" + lixDatatypeToString(leftType) + ") does not match type of right operand (" + lixDatatypeToString(rightType) + ")");
    }

    LixDatatype resultingType = rightType;

    switch (p_pExpr->getOperator())
    {
    case BinaryExpr::BO_ADD:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->getLine(), "Cannot add two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_ADD_BYTE + (uint8_t)resultingType);
        break;
    case BinaryExpr::BO_MUL:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->getLine(), "Cannot multiply two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_MULTIPLY_BYTE + (uint8_t)resultingType);
        break;
    case BinaryExpr::BO_SUB:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->getLine(), "Cannot subtract two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_SUBTRACT_BYTE + (uint8_t)resultingType);
        break;
    case BinaryExpr::BO_DIV:
        if (resultingType == LixDatatype::LD_Bool)
        {
            error(p_pExpr->getLine(), "Cannot divide two boolean values");
        }
        currentChunk()->write((uint8_t)Chunk::OpCode::OP_DIVIDE_BYTE + (uint8_t)resultingType);
        break;
    }
    m_Stack.pop_back();
}
void Compiler::visitUnary(UnaryExpr *p_pExpr)
{
    p_pExpr->getExpr()->visit(this);
    if (m_Stack.back() == LixDatatype::LD_Bool && p_pExpr->getOperator() == UnaryExpr::UnaryOperator::UO_MINUS)
    {
        error(p_pExpr->getLine(), "Dont use \'-\' to negate bool use \'!\' instead.");
    }
    if (m_Stack.back() < LixDatatype::LD_Bool && p_pExpr->getOperator() == UnaryExpr::UnaryOperator::UO_MINUS)
    {
        error(p_pExpr->getLine(), "Dont use \'!\' to negate numerical values use \'-\' instead.");
    }
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_NEGATE_BYTE + (uint8_t)m_Stack.back());
}
void Compiler::visitGrouping(GroupingExpr *p_pExpr)
{
    p_pExpr->getExpr()->visit(this);
}

void Compiler::visitNumber(NumberExpr<Lix_Byte> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_BYTE);
    uint8_t id = currentChunk()->addConstant<Lix_Byte>(p_pExpr->getNumber());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Byte);
}
void Compiler::visitNumber(NumberExpr<Lix_Double> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_DOUBLE);
    uint8_t id = currentChunk()->addConstant<Lix_Double>(p_pExpr->getNumber());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Double);
}
void Compiler::visitNumber(NumberExpr<Lix_Float> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_FLOAT);
    uint8_t id = currentChunk()->addConstant<Lix_Float>(p_pExpr->getNumber());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Float);
}
void Compiler::visitNumber(NumberExpr<Lix_Int> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_INT);
    uint8_t id = currentChunk()->addConstant<Lix_Int>(p_pExpr->getNumber());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_Int);
}
void Compiler::visitNumber(NumberExpr<Lix_LongInt> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_LONGINT);
    uint8_t id = currentChunk()->addConstant<Lix_LongInt>(p_pExpr->getNumber());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_LongInt);
}
void Compiler::visitNumber(NumberExpr<Lix_ShortInt> *p_pExpr)
{
    currentChunk()->write(Chunk::OpCode::OP_CONSTANT_SHORTINT);
    uint8_t id = currentChunk()->addConstant<Lix_ShortInt>(p_pExpr->getNumber());
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_ShortInt);
}

void Compiler::visitBoolean(BooleanExpr *p_pExpr)
{
    if (p_pExpr->getBoolean())
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
    p_pExpr->getExpr()->visit(this);
    LixDatatype from = m_Stack.back();
    if (from != p_pExpr->getTo())
    {
        m_Stack.pop_back();
        currentChunk()->write(cast(from, p_pExpr->getTo()));
        m_Stack.push_back(p_pExpr->getTo());
    }
}

void Compiler::visitVar(VarExpr *p_pExpr)
{
    std::pair<uint32_t, LixDatatype> var = resolveVar(p_pExpr);
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
    p_pExpr->getLeft()->visit(this);
    unsigned int elseJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    unsigned int endJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP);
    currentChunk()->patchJump(elseJump);
    popOne();
    p_pExpr->getRight()->visit(this);
    currentChunk()->patchJump(endJump);
    m_Stack.pop_back();
}
void Compiler::visitAnd(AndExpr *p_pExpr)
{
    p_pExpr->getLeft()->visit(this);
    unsigned int endJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    popOne();
    p_pExpr->getRight()->visit(this);
    currentChunk()->patchJump(endJump);
    m_Stack.pop_back();
}
void Compiler::visitComparison(ComparisonExpr *p_pExpr)
{
    p_pExpr->getLeft()->visit(this);
    LixDatatype leftType = m_Stack.back();

    p_pExpr->getRight()->visit(this);
    LixDatatype rightType = m_Stack.back();

    if (rightType != leftType)
    {
        error(p_pExpr->getLine(), "Type of left operand (" + lixDatatypeToString(leftType) + ") does not match type of right operand (" + lixDatatypeToString(rightType) + ")");
    }

    switch (p_pExpr->getOperator())
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

    Lix_Func func = new ObjFunction(p_pStmt->getName(), stack_offset);
    Compiler comp(m_Logger, func, p_pStmt->get_return_type());
    for (auto &&arg : *p_pStmt)
    {
        comp.addVar(Variable(arg.first, arg.second, 0, p_pStmt->getLine()));
    }

    comp.compile(p_pStmt->getBody());
    func->getChunk()->disassemble(p_pStmt->getName());

    addVar(Variable(LixDatatype::LD_FUNC, p_pStmt->getName(), m_uiCurrentDepth, p_pStmt->getLine()));
    m_Stack.push_back(LixDatatype::LD_FUNC);
    currentChunk()->write(Chunk::OpCode::OP_PUSH_FUNC, p_pStmt->getLine());

    uint8_t id = currentChunk()->addConstant(func);
    currentChunk()->write(id);
    m_Stack.push_back(LixDatatype::LD_FUNC);
}

void Compiler::visitReturnStmt(ReturnStmt *p_pStmt)
{
    p_pStmt->getExpr()->visit(this);
}

void Compiler::visitPrint(PrintStmt *p_pStmt)
{
    p_pStmt->getExpr()->visit(this);
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
    while (m_Variables.size() != 0 && m_Variables.back().getDepth() > m_uiCurrentDepth)
    {
        m_Variables.pop_back();
        pops++;
    }

    popStack(pops);
}
void Compiler::visitVar(VarStmt *p_pStmt)
{
    addVar(Variable(p_pStmt->getType(), p_pStmt->getName(), m_uiCurrentDepth, p_pStmt->getLine()));
    if (p_pStmt->getInitializer() != nullptr)
    {
        p_pStmt->getInitializer()->visit(this);
        if (m_Stack.back() != p_pStmt->getType())
        {
            currentChunk()->write(cast(m_Stack.back(), p_pStmt->getType()));
            m_Stack.pop_back();
            m_Stack.push_back(p_pStmt->getType());
        }
    }
    else
    {
        pushZero(p_pStmt->getType());
    }
}

void Compiler::visitIf(IfStmt *p_pStmt)
{
    p_pStmt->getCondition()->visit(this);
    unsigned int thenJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    popOne();
    p_pStmt->getThen()->visit(this);
    unsigned int elseJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP);
    currentChunk()->patchJump(thenJump);
    popOne();
    if (p_pStmt->getElse() != nullptr)
    {
        p_pStmt->getElse()->visit(this);
    }
    currentChunk()->patchJump(elseJump);
    m_Stack.pop_back();
}

void Compiler::visitWhile(WhileStmt *p_pStmt)
{
    unsigned int loopStart = currentChunk()->getChunkPos();
    p_pStmt->getCondition()->visit(this);
    unsigned int exitJump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
    popOne();
    p_pStmt->getBody()->visit(this);
    currentChunk()->emitLoop(loopStart);
    currentChunk()->patchJump(exitJump);
    popOne();
    m_Stack.pop_back();
}
void Compiler::visitFor(ForStmt *p_pStmt)
{
    if (p_pStmt->getInitializer() != nullptr)
    {
        p_pStmt->getInitializer()->visit(this);
    }
    unsigned int loopStart = currentChunk()->getChunkPos();
    unsigned int jump = 0;
    if (p_pStmt->getCondition() != nullptr)
    {
        p_pStmt->getCondition()->visit(this);
        jump = currentChunk()->emitJump(Chunk::OpCode::OP_JUMP_IF_FALSE);
        popOne();
    }
    p_pStmt->getBody()->visit(this);
    if (p_pStmt->getIncrement() != nullptr)
    {
        p_pStmt->getIncrement()->visit(this);
        popOne(true);
    }
    currentChunk()->emitLoop(loopStart);
    if (p_pStmt->getCondition() != nullptr)
    {
        currentChunk()->patchJump(jump);
        popOne();
        m_Stack.pop_back();
    }
    //popStack(p_pStmt->getPops());
}
void Compiler::visitExprStmt(ExprStmt *p_pStmt)
{
    p_pStmt->getExpr()->visit(this);
    popOne(true);
}

void Compiler::visitCall(CallExpr *p_pExpr)
{
    //m_Stack.push_back(p_pExpr->)
    for (auto &&expr : *p_pExpr)
    {
        expr->visit(this);
    }
    p_pExpr->get_callee()->visit(this);
    currentChunk()->write(Chunk::OpCode::OP_CALL_FUNC, p_pExpr->getLine());
    currentChunk()->write(size_of_variables());
    for (auto &&expr : *p_pExpr)
    {
        m_Stack.pop_back();
    }
}

void Compiler::visitAssign(AssignExpr *p_pExpr)
{
    p_pExpr->getExpr()->visit(this);
    currentChunk()->write((uint8_t)Chunk::OpCode::OP_SET_BYTE + (uint8_t)m_Stack.back());
    std::pair<uint32_t, LixDatatype> var = resolveVar(p_pExpr->getVarExpr());
    uint32_t offset = var.first;
    uint8_t a = offset & 0xFF;
    uint8_t b = offset >> 8;
    currentChunk()->write(a);
    currentChunk()->write(b);
}

Lix_Func Compiler::compile(BlockStmt* block)
{
    m_uiCurrentDepth = 0;
    for (auto &&stmt : *block)
    {
        stmt->visit(this);
    }
    //popStack(m_Stack.size());
    currentChunk()->write(Chunk::OpCode::OP_RETURN);
    return function;
}