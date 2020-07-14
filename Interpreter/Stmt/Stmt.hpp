#pragma once
class VisitorStmt;
class Stmt
{
private:
unsigned int m_uiLine;
public:
    Stmt(unsigned int p_uiLine);
    virtual ~Stmt();
    virtual void visit(VisitorStmt *p_pVisitor) = 0;
    virtual unsigned int getLine();
};
