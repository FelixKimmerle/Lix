#pragma once
#include "Expr.hpp"

class GroupingExpr : public Expr
{
private:
    ExprPtr m_pExpr;

public:
    GroupingExpr(ExprPtr p_pExpr,unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Expr * getExpr();
};

