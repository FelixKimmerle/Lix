#pragma once

#include "Expr.hpp"
#include "VarExpr.hpp"

class AssignExpr : public Expr
{
private:
    std::unique_ptr<VarExpr> var_expr;
    ExprPtr expr;

public:
    AssignExpr(std::unique_ptr<VarExpr> var_expr, ExprPtr expr, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Expr *get_expr();
    VarExpr *get_var_expr();
};
