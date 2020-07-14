#include "BinaryExpr.hpp"
#include "VisitorExpr.hpp"

BinaryExpr::BinaryExpr(Expr *p_pLeft, Expr *p_pRight, BinaryExpr::BinaryOperator p_BinaryOperator, unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pLeft = p_pLeft;
    m_pRight = p_pRight;
    m_BinaryOperator = p_BinaryOperator;
}

BinaryExpr::~BinaryExpr()
{
    delete m_pLeft;
    delete m_pRight;
}

void BinaryExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitBinary(this);
}

Expr *BinaryExpr::getLeft()
{
    return m_pLeft;
}
Expr *BinaryExpr::getRight()
{
    return m_pRight;
}
BinaryExpr::BinaryOperator BinaryExpr::getOperator()
{
    return m_BinaryOperator;
}
