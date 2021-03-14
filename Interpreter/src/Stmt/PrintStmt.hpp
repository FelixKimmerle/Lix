#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class PrintStmt : public Stmt
{
private:
    ExprPtr m_pExpr;
public:
    PrintStmt(ExprPtr p_pExpr,unsigned int p_uiLine);
    void visit(VisitorStmt *p_pVisitor);
    Expr * getExpr();
};
