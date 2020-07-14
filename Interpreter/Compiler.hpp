#pragma once
#include "Expr/VisitorExpr.hpp"
#include "Stmt/VisitorStmt.hpp"
#include "Variable.hpp"
#include "Chunk.hpp"
#include <optional>
#include "Logger.hpp"
#include "ObjFunction.hpp"

class Compiler : VisitorExpr, VisitorStmt
{
private:
    ObjFunction function;
    std::vector<LixDatatype> m_Stack;
    Chunk::OpCode cast(LixDatatype p_From, LixDatatype p_To);
    void popStack(unsigned int n);
    void popOne(bool moditernstack = false);
    void pushZero(LixDatatype m_Type);
    void error(unsigned int line, const std::string &message);
    bool m_bHadError;
    Logger *m_Logger;

    unsigned int m_uiCurrentDepth;

    std::vector<Variable> m_Variables;
    void addVar(Variable variable);
    std::pair<uint32_t, LixDatatype> resolveVar(VarExpr *p_pExpr);

    Chunk *currentChunk();

public:
    Compiler(Logger *p_Logger);
    virtual ~Compiler();

    virtual void visitBinary(BinaryExpr *p_pExpr);
    virtual void visitUnary(UnaryExpr *p_pExpr);
    virtual void visitGrouping(GroupingExpr *p_pExpr);
    virtual void visitNumber(NumberExpr<Lix_Byte> *p_pExpr);
    virtual void visitNumber(NumberExpr<Lix_Double> *p_pExpr);
    virtual void visitNumber(NumberExpr<Lix_Float> *p_pExpr);
    virtual void visitNumber(NumberExpr<Lix_Int> *p_pExpr);
    virtual void visitNumber(NumberExpr<Lix_LongInt> *p_pExpr);
    virtual void visitNumber(NumberExpr<Lix_ShortInt> *p_pExpr);
    virtual void visitBoolean(BooleanExpr *p_pExpr);
    virtual void visitExplicitCast(ExplicitCastExpr *p_pExpr);
    virtual void visitVar(VarExpr *p_pExpr);
    virtual void visitAssign(AssignExpr *p_pExpr);
    virtual void visitOr(OrExpr *p_pExpr);
    virtual void visitAnd(AndExpr *p_pExpr);
    virtual void visitComparison(ComparisonExpr *p_pExpr);
	virtual void visitFuncDecl(FuncDecl* p_pStmt);
	virtual void visitReturnStmt(ReturnStmt *p_pStmt);

    virtual void visitPrint(PrintStmt *p_pStmt);
    virtual void visitBlock(BlockStmt *p_pStmt);
    virtual void visitVar(VarStmt *p_pStmt);
    virtual void visitIf(IfStmt *p_pStmt);
    virtual void visitWhile(WhileStmt *p_pStmt);
    virtual void visitFor(ForStmt *p_pStmt);
    virtual void visitExprStmt(ExprStmt *p_pStmt);
    virtual void visitFunc(FuncExpr *p_pExpr);

    ObjFunction *compile(const std::vector<Stmt *> &p_vStmts);
    bool hadError();
};
