#pragma once

#include "Expr.hpp"

class ComparisonExpr : public Expr
{
public:
    enum ComparisonOperator
    {
        BO_EQUAL,
        BO_LESS,
        BO_LESS_EQUAL,
        BO_GREATER,
        BO_GREATER_EQUAL,
    };

private:
    ExprPtr m_pLeft;
    ExprPtr m_pRight;
    ComparisonOperator m_BinaryOperator;
public:
    ComparisonExpr(ExprPtr p_pLeft, ExprPtr p_pRight, ComparisonExpr::ComparisonOperator p_BinaryOperator,unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Expr * getLeft();
    Expr * getRight();
    ComparisonOperator getOperator();
};
