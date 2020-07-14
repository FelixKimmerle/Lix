#include "ComparisonExpr.hpp"
#include "VisitorExpr.hpp"

ComparisonExpr::ComparisonExpr(Expr *p_pLeft, Expr *p_pRight, ComparisonExpr::ComparisonOperator p_BinaryOperator,unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pLeft = p_pLeft;
    m_pRight = p_pRight;
    m_BinaryOperator = p_BinaryOperator;
}

ComparisonExpr::~ComparisonExpr()
{
    delete m_pLeft;
    delete m_pRight;
}

void ComparisonExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitComparison(this);
}

Expr *ComparisonExpr::getLeft()
{
    return m_pLeft;
}
Expr *ComparisonExpr::getRight()
{
    return m_pRight;
}
ComparisonExpr::ComparisonOperator ComparisonExpr::getOperator()
{
    return m_BinaryOperator;
}
