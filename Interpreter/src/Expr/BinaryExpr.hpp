#pragma once

#include "Expr.hpp"

class BinaryExpr : public Expr
{
public:
    enum BinaryOperator
    {
        BO_ADD,
        BO_SUB,
        BO_MUL,
        BO_DIV,
    };

private:
    ExprPtr m_pLeft;
    ExprPtr m_pRight;
    BinaryOperator m_BinaryOperator;

public:
    BinaryExpr(ExprPtr p_pLeft, ExprPtr p_pRight, BinaryExpr::BinaryOperator p_BinaryOperator, unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Expr *getLeft();
    Expr *getRight();
    BinaryOperator getOperator();
};
