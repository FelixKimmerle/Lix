#pragma once
#include "Expr.hpp"

class GroupingExpr : public Expr
{
private:
    Expr *m_pExpr;

public:
    GroupingExpr(Expr *p_pExpr,unsigned int p_uiLine);
    ~GroupingExpr();
    void visit(VisitorExpr *p_pVisitor);
    Expr * getExpr();
};

