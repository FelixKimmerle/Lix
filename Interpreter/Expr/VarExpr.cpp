#include "VarExpr.hpp"
#include "VisitorExpr.hpp"
VarExpr::VarExpr(std::string p_sName, unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_sName = p_sName;
}

VarExpr::~VarExpr()
{
}

void VarExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitVar(this);
}

std::string VarExpr::getName()
{
    return m_sName;
}
