#include "Stmt/ExprStmt.hpp"
#include "Stmt/VisitorStmt.hpp"

ExprStmt::ExprStmt(ExprPtr p_pExpr, unsigned int p_uiLine) : m_pExpr(std::move(p_pExpr)),
                                                             Stmt(p_uiLine)
{
}

void ExprStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitExprStmt(this);
}

Expr *ExprStmt::getExpr()
{
    return m_pExpr.get();
}