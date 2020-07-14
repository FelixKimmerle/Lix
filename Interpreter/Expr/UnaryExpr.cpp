#include "UnaryExpr.hpp"
#include "VisitorExpr.hpp"
UnaryExpr::UnaryExpr(Expr *p_pExpr, UnaryOperator p_UnaryOperator, unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pExpr = p_pExpr;
    m_UnaryOperator = p_UnaryOperator;
}

UnaryExpr::~UnaryExpr()
{
    delete m_pExpr;
}

void UnaryExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitUnary(this);
}

Expr *UnaryExpr::getExpr()
{
    return m_pExpr;
}

UnaryExpr::UnaryOperator UnaryExpr::getOperator()
{
    return m_UnaryOperator;
}