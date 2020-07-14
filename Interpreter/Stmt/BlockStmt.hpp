#pragma once

#include "Stmt/Stmt.hpp"
#include <vector>

class BlockStmt : public Stmt
{
private:
    std::vector<Stmt *> m_vStmts;

public:
    BlockStmt(const std::vector<Stmt *> &p_vStmts, unsigned int p_uiLine);
    virtual ~BlockStmt();
    virtual void visit(VisitorStmt *p_pVisitor);
    std::vector<Stmt *>::iterator begin();
    std::vector<Stmt *>::iterator end();
};
