#include "OrExpr.hpp"
#include "VisitorExpr.hpp"
OrExpr::OrExpr(ExprPtr p_pLeft, ExprPtr p_pRight, unsigned int p_uiLine) : m_pLeft(std::move(p_pLeft)),
                                                                           m_pRight(std::move(p_pRight)),
                                                                           Expr(p_uiLine)
{
}

void OrExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitOr(this);
}
Expr *OrExpr::getLeft()
{
    return m_pLeft.get();
}
Expr *OrExpr::getRight()
{
    return m_pRight.get();
}