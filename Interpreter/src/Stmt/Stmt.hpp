#pragma once

#include "TokenPosition.hpp"

#include <memory>

class VisitorStmt;
class Stmt
{
private:
    TokenPosition position;

public:
    Stmt(TokenPosition position);
    virtual void visit(VisitorStmt *visitor) = 0;
    virtual TokenPosition get_position();
};

typedef std::unique_ptr<Stmt> StmtPtr;