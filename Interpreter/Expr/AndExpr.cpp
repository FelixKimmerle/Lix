#include "AndExpr.hpp"
#include "VisitorExpr.hpp"
AndExpr::AndExpr(Expr *p_pLeft, Expr *p_pRight,unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pLeft = p_pLeft;
    m_pRight = p_pRight;
}

AndExpr::~AndExpr()
{
}
void AndExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitAnd(this);
}
Expr *AndExpr::getLeft()
{
    return m_pLeft;
}
Expr *AndExpr::getRight()
{
    return m_pRight;
}