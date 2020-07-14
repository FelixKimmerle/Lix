#include "VarStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
VarStmt::VarStmt(std::string p_sName,LixDatatype p_Type, Expr *p_Initializer,unsigned int p_uiLine) : Stmt(p_uiLine)
{
    m_sName = p_sName;
    m_Type = p_Type;
    m_Initializer = p_Initializer;
}

VarStmt::~VarStmt()
{
    if (m_Initializer != nullptr)
    {
        delete m_Initializer;
    }
}

void VarStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitVar(this);
}

Expr *VarStmt::getInitializer()
{
    return m_Initializer;
}

LixDatatype VarStmt::getType()
{
    return m_Type;
}

std::string VarStmt::getName()
{
    return m_sName;
}