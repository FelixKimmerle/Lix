#pragma once
#include "BinaryExpr.hpp"
#include "UnaryExpr.hpp"
#include "GroupingExpr.hpp"
#include "BooleanExpr.hpp"
#include "NumberExpr.hpp"
#include "ExplicitCastExpr.hpp"
#include "VarExpr.hpp"
#include "AssignExpr.hpp"
#include "OrExpr.hpp"
#include "AndExpr.hpp"
#include "ComparisonExpr.hpp"
#include "CallExpr.hpp"

class VisitorExpr
{
public:
    virtual void visitBinary(BinaryExpr *p_pExpr) = 0;
    virtual void visitUnary(UnaryExpr *p_pExpr) = 0;
    virtual void visitGrouping(GroupingExpr *p_pExpr) = 0;
    virtual void visitBoolean(BooleanExpr *p_pExpr) = 0;
    virtual void visitNumber(NumberExpr<Lix_Byte> *p_pExpr) = 0;
    virtual void visitNumber(NumberExpr<Lix_Double> *p_pExpr) = 0;
    virtual void visitNumber(NumberExpr<Lix_Float> *p_pExpr) = 0;
    virtual void visitNumber(NumberExpr<Lix_Int> *p_pExpr) = 0;
    virtual void visitNumber(NumberExpr<Lix_LongInt> *p_pExpr) = 0;
    virtual void visitNumber(NumberExpr<Lix_ShortInt> *p_pExpr) = 0;
    virtual void visitExplicitCast(ExplicitCastExpr *p_pExpr) = 0;
    virtual void visitVar(VarExpr *p_pExpr) = 0;
    virtual void visitAssign(AssignExpr *p_pExpr) = 0;
    virtual void visitOr(OrExpr *p_pExpr) = 0;
    virtual void visitAnd(AndExpr *p_pExpr) = 0;
    virtual void visitComparison(ComparisonExpr *p_pExpr) = 0;
    virtual void visitCall(CallExpr *p_pExpr) = 0;
};

