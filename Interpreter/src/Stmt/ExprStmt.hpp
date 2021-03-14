#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class ExprStmt : public Stmt
{
private:
    ExprPtr m_pExpr;

public:
    ExprStmt(ExprPtr p_pExpr, unsigned int p_uiLine);
    void visit(VisitorStmt *p_pVisitor);
    Expr *getExpr();
};
