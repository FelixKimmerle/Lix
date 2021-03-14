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
    ExprPtr m_pExpr;
    UnaryOperator m_UnaryOperator;

public:
    UnaryExpr(ExprPtr p_pExpr, UnaryOperator p_UnaryOperator, unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Expr *getExpr();
    UnaryOperator getOperator();
};
