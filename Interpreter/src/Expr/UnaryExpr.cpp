#include "UnaryExpr.hpp"
#include "VisitorExpr.hpp"
UnaryExpr::UnaryExpr(ExprPtr expr, UnaryOperator unary_operator, TokenPosition position) : Expr(position),
                                                                                               expr(std::move(expr)),
                                                                                               unary_operator(unary_operator)

{
}

void UnaryExpr::visit(VisitorExpr *visitor)
{
    visitor->visitUnary(this);
}

Expr *UnaryExpr::get_expr()
{
    return expr.get();
}

UnaryExpr::UnaryOperator UnaryExpr::get_unary_operator()
{
    return unary_operator;
}