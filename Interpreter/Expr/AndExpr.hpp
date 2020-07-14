#pragma once
#include "Expr.hpp"

class AndExpr : public Expr
{
private:
    Expr *m_pLeft;
    Expr *m_pRight;

public:
    AndExpr(Expr *p_pLeft, Expr *p_pRight,unsigned int p_uiLine);
    ~AndExpr();
    void visit(VisitorExpr *p_pVisitor);
    Expr *getLeft();
    Expr *getRight();
};

