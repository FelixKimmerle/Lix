#include "AssignExpr.hpp"
#include "VisitorExpr.hpp"

AssignExpr::AssignExpr(std::unique_ptr<VarExpr> var_expr, ExprPtr expr, TokenPosition position) : Expr(position),
                                                                                                  expr(std::move(expr)),
                                                                                                  var_expr(std::move(var_expr))

{
}

void AssignExpr::visit(VisitorExpr *visitor)
{
    visitor->visitAssign(this);
}

Expr *AssignExpr::get_expr()
{
    return expr.get();
}

VarExpr *AssignExpr::get_var_expr()
{
    return var_expr.get();
}