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
    Expr *m_pLeft;
    Expr *m_pRight;
    BinaryOperator m_BinaryOperator;
public:
    BinaryExpr(Expr *p_pLeft, Expr *p_pRight, BinaryExpr::BinaryOperator p_BinaryOperator,unsigned int p_uiLine);
    ~BinaryExpr();
    void visit(VisitorExpr *p_pVisitor);
    Expr * getLeft();
    Expr * getRight();
    BinaryOperator getOperator();
};
