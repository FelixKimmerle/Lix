#include "UnaryExpr.hpp"
#include "VisitorExpr.hpp"
UnaryExpr::UnaryExpr(ExprPtr p_pExpr, UnaryOperator p_UnaryOperator, unsigned int p_uiLine) : m_pExpr(std::move(p_pExpr)),
                                                                                              m_UnaryOperator(p_UnaryOperator),
                                                                                              Expr(p_uiLine)
{
}

void UnaryExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitUnary(this);
}

Expr *UnaryExpr::getExpr()
{
    return m_pExpr.get();
}

UnaryExpr::UnaryOperator UnaryExpr::getOperator()
{
    return m_UnaryOperator;
}