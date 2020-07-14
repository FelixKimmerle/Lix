#include "ExplicitCastExpr.hpp"
#include "VisitorExpr.hpp"
ExplicitCastExpr::ExplicitCastExpr(Expr *p_pExpr, LixDatatype p_Type, unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pExpr = p_pExpr;
    m_to = p_Type;
}
ExplicitCastExpr::~ExplicitCastExpr()
{
    delete m_pExpr;
}
void ExplicitCastExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitExplicitCast(this);
}
Expr *ExplicitCastExpr::getExpr()
{
    return m_pExpr;
}
LixDatatype ExplicitCastExpr::getTo()
{
    return m_to;
}