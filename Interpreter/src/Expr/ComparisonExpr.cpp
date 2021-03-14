#include "ComparisonExpr.hpp"
#include "VisitorExpr.hpp"

ComparisonExpr::ComparisonExpr(ExprPtr p_pLeft, ExprPtr p_pRight, ComparisonExpr::ComparisonOperator p_BinaryOperator, unsigned int p_uiLine) : m_pLeft(std::move(p_pLeft)),
                                                                                                                                                m_pRight(std::move(p_pRight)),
                                                                                                                                                m_BinaryOperator(p_BinaryOperator),
                                                                                                                                                Expr(p_uiLine)
{
}

void ComparisonExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitComparison(this);
}

Expr *ComparisonExpr::getLeft()
{
    return m_pLeft.get();
}
Expr *ComparisonExpr::getRight()
{
    return m_pRight.get();
}
ComparisonExpr::ComparisonOperator ComparisonExpr::getOperator()
{
    return m_BinaryOperator;
}
