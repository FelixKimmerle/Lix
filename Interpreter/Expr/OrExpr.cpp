#include "OrExpr.hpp"
#include "VisitorExpr.hpp"
OrExpr::OrExpr(Expr *p_pLeft, Expr *p_pRight,unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pLeft = p_pLeft;
    m_pRight = p_pRight;
}

OrExpr::~OrExpr()
{
}
void OrExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitOr(this);
}
Expr *OrExpr::getLeft()
{
    return m_pLeft;
}
Expr *OrExpr::getRight()
{
    return m_pRight;
}