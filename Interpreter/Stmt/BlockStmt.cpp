#include "Stmt/BlockStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
BlockStmt::BlockStmt(const std::vector<Stmt *> &p_vStmts, unsigned int p_uiLine) : Stmt(p_uiLine)
{
    m_vStmts = p_vStmts;
}

BlockStmt::~BlockStmt()
{
    for (auto &&stmt : m_vStmts)
    {
        delete stmt;
    }
}

void BlockStmt::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitBlock(this);
}

std::vector<Stmt *>::iterator BlockStmt::begin()
{
    return m_vStmts.begin();
}
std::vector<Stmt *>::iterator BlockStmt::end()
{
    return m_vStmts.end();
}
