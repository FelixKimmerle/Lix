#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class ExprStmt : public Stmt
{
private:
    Expr *m_pExpr;

public:
    ExprStmt(Expr *p_pExpr, unsigned int p_uiLine);
    virtual ~ExprStmt();
    void visit(VisitorStmt *p_pVisitor);
    Expr *getExpr();
};
