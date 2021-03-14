#include "Stmt/PrintStmt.hpp"
#include "Stmt/VisitorStmt.hpp"

PrintStmt::PrintStmt(ExprPtr p_pExpr, unsigned int p_uiLine) : m_pExpr(std::move(p_pExpr)),
                                                               Stmt(p_uiLine)
{
}

void PrintStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitPrint(this);
}

Expr *PrintStmt::getExpr()
{
    return m_pExpr.get();
}