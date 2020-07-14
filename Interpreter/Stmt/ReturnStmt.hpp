#pragma once
#include "Stmt.hpp"
#include "Expr/Expr.hpp"
class ReturnStmt : public Stmt
{
private:
    Expr *m_pExpr;

public:
    ReturnStmt(Expr *p_pExpr, unsigned int p_uiLine);
    ~ReturnStmt();
    void visit(VisitorStmt *p_pVisitor);
    Expr *getExpr();
};

