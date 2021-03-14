#include "BinaryExpr.hpp"
#include "VisitorExpr.hpp"

BinaryExpr::BinaryExpr(ExprPtr p_pLeft, ExprPtr p_pRight, BinaryExpr::BinaryOperator p_BinaryOperator, unsigned int p_uiLine) : m_pLeft(std::move(p_pLeft)),
                                                                                                                                m_pRight(std::move(p_pRight)),
                                                                                                                                m_BinaryOperator(p_BinaryOperator),
                                                                                                                                Expr(p_uiLine)
{
}

void BinaryExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitBinary(this);
}

Expr *BinaryExpr::getLeft()
{
    return m_pLeft.get();
}
Expr *BinaryExpr::getRight()
{
    return m_pRight.get();
}
BinaryExpr::BinaryOperator BinaryExpr::getOperator()
{
    return m_BinaryOperator;
}
