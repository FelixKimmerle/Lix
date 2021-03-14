#include "GroupingExpr.hpp"
#include "VisitorExpr.hpp"

GroupingExpr::GroupingExpr(ExprPtr p_pExpr, unsigned int p_uiLine) : m_pExpr(std::move(p_pExpr)),
                                                                     Expr(p_uiLine)
{
}

void GroupingExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitGrouping(this);
}

Expr *GroupingExpr::getExpr()
{
    return m_pExpr.get();
}
