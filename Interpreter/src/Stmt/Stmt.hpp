#pragma once

#include <memory>

class VisitorStmt;
class Stmt
{
private:
    unsigned int m_uiLine;

public:
    Stmt(unsigned int p_uiLine);
    virtual void visit(VisitorStmt *p_pVisitor) = 0;
    virtual unsigned int getLine();
};

typedef std::unique_ptr<Stmt> StmtPtr;