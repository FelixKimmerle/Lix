#pragma once

#include "Stmt/Stmt.hpp"
#include <vector>

class BlockStmt : public Stmt
{
private:
    std::vector<StmtPtr> stmts;

public:
    BlockStmt(TokenPosition position);
    virtual void visit(VisitorStmt *visitor);
    std::vector<StmtPtr>::const_iterator begin()const;
    std::vector<StmtPtr>::const_iterator end()const;
    void add(StmtPtr stmt);
};
