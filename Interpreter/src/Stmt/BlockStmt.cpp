#include "Stmt/BlockStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
BlockStmt::BlockStmt(TokenPosition position) : Stmt(position)
{
}

void BlockStmt::visit(VisitorStmt *visitor)
{
    visitor->visitBlock(this);
}

std::vector<StmtPtr>::const_iterator BlockStmt::begin()const
{
    return stmts.cbegin();
}
std::vector<StmtPtr>::const_iterator BlockStmt::end()const
{
    return stmts.cend();
}

void BlockStmt::add(StmtPtr stmt)
{
    stmts.push_back(std::move(stmt));
}