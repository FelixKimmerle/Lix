#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class PrintStmt : public Stmt
{
private:
    Expr * m_pExpr;
public:
    PrintStmt(Expr * p_pExpr,unsigned int p_uiLine);
    virtual ~PrintStmt();
    void visit(VisitorStmt *p_pVisitor);
    Expr * getExpr();
};
