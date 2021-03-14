#include "AndExpr.hpp"
#include "VisitorExpr.hpp"

AndExpr::AndExpr(ExprPtr p_pLeft, ExprPtr p_pRight, unsigned int p_uiLine) : m_pLeft(std::move(p_pLeft)),
                                                                             m_pRight(std::move(p_pRight)),
                                                                             Expr(p_uiLine)
{
}

void AndExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitAnd(this);
}
Expr *AndExpr::getLeft()
{
    return m_pLeft.get();
}
Expr *AndExpr::getRight()
{
    return m_pRight.get();
}