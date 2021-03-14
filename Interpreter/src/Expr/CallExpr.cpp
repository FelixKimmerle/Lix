#include "CallExpr.hpp"
#include "VisitorExpr.hpp"

CallExpr::CallExpr(ExprPtr callee, unsigned int p_uiLine) : Expr(p_uiLine), callee(std::move(callee))
{
}

void CallExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitCall(this);
}

std::vector<ExprPtr>::iterator CallExpr::begin()
{
    return m_vParams.begin();
}
std::vector<ExprPtr>::iterator CallExpr::end()
{
    return m_vParams.end();
}

Expr *CallExpr::get_callee()
{
    return callee.get();
}

void CallExpr::add_param(ExprPtr param)
{
    m_vParams.push_back(std::move(param));
}