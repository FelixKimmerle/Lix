#include "ReturnStmt.hpp"
#include "VisitorStmt.hpp"
ReturnStmt::ReturnStmt(Expr *p_pExpr, unsigned int p_uiLine) : Stmt(p_uiLine)
{
    m_pExpr = p_pExpr;
}

ReturnStmt::~ReturnStmt()
{
    delete m_pExpr;
}

Expr *ReturnStmt::getExpr()
{
    return m_pExpr;
}

void ReturnStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitReturnStmt(this);
}