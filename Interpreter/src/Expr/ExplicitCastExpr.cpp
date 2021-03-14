#include "ExplicitCastExpr.hpp"
#include "VisitorExpr.hpp"
ExplicitCastExpr::ExplicitCastExpr(ExprPtr p_pExpr, LixDatatype p_Type, unsigned int p_uiLine) : m_pExpr(std::move(p_pExpr)),
                                                                                                 m_to(p_Type),
                                                                                                 Expr(p_uiLine)
{
}

void ExplicitCastExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitExplicitCast(this);
}
Expr *ExplicitCastExpr::getExpr()
{
    return m_pExpr.get();
}
LixDatatype ExplicitCastExpr::getTo()
{
    return m_to;
}