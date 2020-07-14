#include "GroupingExpr.hpp"
#include "VisitorExpr.hpp"

GroupingExpr::GroupingExpr(Expr *p_pExpr,unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pExpr = p_pExpr;
}

GroupingExpr::~GroupingExpr()
{
    delete m_pExpr;
}

void GroupingExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitGrouping(this);
}

Expr *GroupingExpr::getExpr()
{
    return m_pExpr;
}
