#pragma once

#include "Expr.hpp"

class UnaryExpr : public Expr
{
    public:
    enum UnaryOperator
    {
        UO_MINUS,
        UO_BANG,
    };
private:
    Expr *m_pExpr;
    UnaryOperator m_UnaryOperator;
public:
    UnaryExpr(Expr *p_pExpr, UnaryOperator p_UnaryOperator,unsigned int p_uiLine);
    virtual ~UnaryExpr();
    void visit(VisitorExpr *p_pVisitor);
    Expr * getExpr();
    UnaryOperator getOperator();
};

