#include "Stmt/BlockStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
BlockStmt::BlockStmt(unsigned int p_uiLine) : Stmt(p_uiLine)
{
}

void BlockStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitBlock(this);
}

std::vector<StmtPtr>::iterator BlockStmt::begin()
{
    return m_vStmts.begin();
}
std::vector<StmtPtr>::iterator BlockStmt::end()
{
    return m_vStmts.end();
}

void BlockStmt::add(StmtPtr stmt)
{
    m_vStmts.push_back(std::move(stmt));
}