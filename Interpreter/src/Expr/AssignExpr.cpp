#include "AssignExpr.hpp"
#include "VisitorExpr.hpp"

AssignExpr::AssignExpr(std::unique_ptr<VarExpr> p_pVarExpr, ExprPtr p_pExpr, unsigned int p_uiLine) : m_pExpr(std::move(p_pExpr)),
                                                                                                      m_pVarExpr(std::move(p_pVarExpr)),
                                                                                                      Expr(p_uiLine)
{
}

void AssignExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitAssign(this);
}

Expr *AssignExpr::getExpr()
{
    return m_pExpr.get();
}

VarExpr *AssignExpr::getVarExpr()
{
    return m_pVarExpr.get();
}