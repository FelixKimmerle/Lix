#pragma once

#include "Expr.hpp"
#include "VarExpr.hpp"

class AssignExpr : public Expr
{
private:
    VarExpr *m_pVarExpr;
    Expr *m_pExpr;

public:
    AssignExpr(VarExpr *p_pVarExpr, Expr *p_pExpr,unsigned int p_uiLine);
    ~AssignExpr();
    Expr *getExpr();
    VarExpr *getVarExpr();
    void visit(VisitorExpr *p_pVisitor);
};
