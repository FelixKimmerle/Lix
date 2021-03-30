#pragma once
#include "Stmt.hpp"
#include "Expr/Expr.hpp"
class ReturnStmt : public Stmt
{
private:
    ExprPtr expr;

public:
    ReturnStmt(ExprPtr expr, TokenPosition position);
    void visit(VisitorStmt *visitor);
    Expr *get_expr();
};

