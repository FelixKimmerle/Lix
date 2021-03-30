#include "OrExpr.hpp"
#include "VisitorExpr.hpp"
OrExpr::OrExpr(ExprPtr left, ExprPtr right, TokenPosition position) : Expr(position),
                                                                      left(std::move(left)),
                                                                      right(std::move(right))

{
}

void OrExpr::visit(VisitorExpr *visitor)
{
    visitor->visitOr(this);
}
Expr *OrExpr::get_left()
{
    return left.get();
}
Expr *OrExpr::get_right()
{
    return right.get();
}