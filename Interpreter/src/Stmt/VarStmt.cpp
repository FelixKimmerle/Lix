#include "VarStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
VarStmt::VarStmt(std::string p_sName, LixDatatype p_Type, ExprPtr p_Initializer, unsigned int p_uiLine) : m_Initializer(std::move(p_Initializer)),
                                                                                                          Stmt(p_uiLine)
{
    m_sName = p_sName;
    m_Type = p_Type;
}

void VarStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitVar(this);
}

Expr *VarStmt::getInitializer()
{
    return m_Initializer.get();
}

LixDatatype VarStmt::getType()
{
    return m_Type;
}

std::string VarStmt::getName()
{
    return m_sName;
}