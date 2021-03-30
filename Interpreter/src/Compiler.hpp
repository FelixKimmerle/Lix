#pragma once
#include "Expr/VisitorExpr.hpp"
#include "Stmt/VisitorStmt.hpp"
#include "Variable.hpp"
#include "Chunk.hpp"
#include <optional>
#include "Logger.hpp"
#include "ObjFunction.hpp"
#include "LixTypenames.hpp"

class Compiler : VisitorExpr, VisitorStmt
{
private:
    Lix_Func function;
    std::vector<LixDatatype> m_Stack;
    Chunk::OpCode cast(LixDatatype p_From, LixDatatype p_To);
    void pop_stack(unsigned int n);
    uint8_t stack_size(unsigned int n);
    void pop_one(bool moditernstack = false);
    void push_zero(LixDatatype m_Type);
    void error(unsigned int line, const std::string &message);
    bool had_error;
    Logger *logger;

    unsigned int m_uiCurrentDepth;
    LixDatatype return_type;

    std::vector<Variable> m_Variables;
    unsigned int size_of_variables();
    void add_var(Variable variable);
    std::pair<uint32_t, LixDatatype> resolve_var(VarExpr *p_pExpr);

    Chunk *currentChunk();

public:
    Compiler(Logger *p_Logger, Lix_Func function, LixDatatype return_type);
    Compiler(Logger *p_Logger, LixDatatype return_type);

    virtual void visitBinary(BinaryExpr *binary_expr);
    virtual void visitUnary(UnaryExpr *unary_expr);
    virtual void visitGrouping(GroupingExpr *grouping_expr);
    virtual void visitNumber(NumberExpr<Lix_Byte> *number_expr);
    virtual void visitNumber(NumberExpr<Lix_Double> *number_expr);
    virtual void visitNumber(NumberExpr<Lix_Float> *number_expr);
    virtual void visitNumber(NumberExpr<Lix_Int> *number_expr);
    virtual void visitNumber(NumberExpr<Lix_LongInt> *number_expr);
    virtual void visitNumber(NumberExpr<Lix_ShortInt> *number_expr);
    virtual void visitBoolean(BooleanExpr *boolean_expr);
    virtual void visitExplicitCast(ExplicitCastExpr *cast_expr);
    virtual void visitVar(VarExpr *var_expr);
    virtual void visitAssign(AssignExpr *assign_expr);
    virtual void visitOr(OrExpr *or_expr);
    virtual void visitAnd(AndExpr *and_expr);
    virtual void visitComparison(ComparisonExpr *comparison_expr);
    virtual void visitFuncDecl(FuncDecl *func_decl_stmt);

    virtual void visitReturnStmt(ReturnStmt *return_stmt);
    virtual void visitPrint(PrintStmt *print_stmt);
    virtual void visitBlock(BlockStmt *block_stmt);
    virtual void visitVar(VarStmt *var_stmt);
    virtual void visitIf(IfStmt *if_stmt);
    virtual void visitWhile(WhileStmt *while_stmt);
    virtual void visitFor(ForStmt *for_stmt);
    virtual void visitExprStmt(ExprStmt *expr_stmt);
    virtual void visitCall(CallExpr *call_expr);

    Lix_Func compile(const BlockStmt &block);
    bool hadError();
};
