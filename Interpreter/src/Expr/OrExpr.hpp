#pragma once
#include "Expr.hpp"

class OrExpr : public Expr
{
private:
    ExprPtr m_pLeft;
    ExprPtr m_pRight;

public:
    OrExpr(ExprPtr p_pLeft, ExprPtr p_pRight,unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Expr *getLeft();
    Expr *getRight();
};

