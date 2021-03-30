#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class PrintStmt : public Stmt
{
private:
    ExprPtr expr;

public:
    PrintStmt(ExprPtr expr, TokenPosition position);
    void visit(VisitorStmt *visitor);
    Expr *get_expr();
};
