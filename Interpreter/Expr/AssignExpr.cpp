#include "AssignExpr.hpp"
#include "VisitorExpr.hpp"

AssignExpr::AssignExpr(VarExpr *p_pVarExpr, Expr *p_pExpr,unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_pExpr = p_pExpr;
    m_pVarExpr = p_pVarExpr;
}

AssignExpr::~AssignExpr()
{
    delete m_pExpr;
    delete m_pVarExpr;
}

Expr *AssignExpr::getExpr()
{
    return m_pExpr;
}

void AssignExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitAssign(this);
}

VarExpr *AssignExpr::getVarExpr()
{
    return m_pVarExpr;
}