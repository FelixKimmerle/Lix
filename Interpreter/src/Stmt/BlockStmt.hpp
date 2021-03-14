#pragma once

#include "Stmt/Stmt.hpp"
#include <vector>

class BlockStmt : public Stmt
{
private:
    std::vector<StmtPtr> m_vStmts;

public:
    BlockStmt(unsigned int p_uiLine);
    virtual void visit(VisitorStmt *p_pVisitor);
    std::vector<StmtPtr>::iterator begin();
    std::vector<StmtPtr>::iterator end();
    void add(StmtPtr stmt);
};
