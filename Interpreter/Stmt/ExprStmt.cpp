#include "Stmt/ExprStmt.hpp"
#include "Stmt/VisitorStmt.hpp"

ExprStmt::ExprStmt(Expr *p_pExpr, unsigned int p_uiLine) : Stmt(p_uiLine)
{
    m_pExpr = p_pExpr;
}

ExprStmt::~ExprStmt()
{
    delete m_pExpr;
}

void ExprStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitExprStmt(this);
}

Expr *ExprStmt::getExpr()
{
    return m_pExpr;
}