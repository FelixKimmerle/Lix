#include "Stmt/PrintStmt.hpp"
#include "Stmt/VisitorStmt.hpp"

PrintStmt::PrintStmt(Expr *p_pExpr,unsigned int p_uiLine) : Stmt(p_uiLine)
{
    m_pExpr = p_pExpr;
}

PrintStmt::~PrintStmt()
{
    delete m_pExpr;
}

void PrintStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitPrint(this);
}

Expr *PrintStmt::getExpr()
{
    return m_pExpr;
}