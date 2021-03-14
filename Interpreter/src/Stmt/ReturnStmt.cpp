#include "ReturnStmt.hpp"
#include "VisitorStmt.hpp"
ReturnStmt::ReturnStmt(ExprPtr p_pExpr, unsigned int p_uiLine) : m_pExpr(std::move(p_pExpr)),
                                                                 Stmt(p_uiLine)
{
}

Expr *ReturnStmt::getExpr()
{
    return m_pExpr.get();
}

void ReturnStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitReturnStmt(this);
}