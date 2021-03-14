#pragma once

#include "Expr.hpp"
#include "VarExpr.hpp"

class AssignExpr : public Expr
{
private:
    std::unique_ptr<VarExpr> m_pVarExpr;
    ExprPtr m_pExpr;

public:
    AssignExpr(std::unique_ptr<VarExpr> p_pVarExpr, ExprPtr p_pExpr,unsigned int p_uiLine);
    Expr *getExpr();
    VarExpr *getVarExpr();
    void visit(VisitorExpr *p_pVisitor);
};
