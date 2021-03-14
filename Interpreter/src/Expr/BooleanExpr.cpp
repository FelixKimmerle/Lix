
#include "BooleanExpr.hpp"
#include "VisitorExpr.hpp"

BooleanExpr::BooleanExpr(Lix_Bool p_Boolean, unsigned int p_uiLine) : m_Boolean(p_Boolean), Expr(p_uiLine)
{
}

void BooleanExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitBoolean(this);
}

Lix_Bool BooleanExpr::getBoolean()
{
    return m_Boolean;
}
