#pragma once
#include "Expr.hpp"

class OrExpr : public Expr
{
private:
    Expr *m_pLeft;
    Expr *m_pRight;

public:
    OrExpr(Expr *p_pLeft, Expr *p_pRight,unsigned int p_uiLine);
    ~OrExpr();
    void visit(VisitorExpr *p_pVisitor);
    Expr *getLeft();
    Expr *getRight();
};

