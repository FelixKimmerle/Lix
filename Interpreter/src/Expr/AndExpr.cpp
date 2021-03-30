#include "AndExpr.hpp"
#include "VisitorExpr.hpp"

AndExpr::AndExpr(ExprPtr left, ExprPtr right, TokenPosition position) : Expr(position),
                                                                        left(std::move(left)),
                                                                        right(std::move(right))

{
}

void AndExpr::visit(VisitorExpr *visitor)
{
    visitor->visitAnd(this);
}
Expr *AndExpr::get_left()
{
    return left.get();
}
Expr *AndExpr::get_right()
{
    return right.get();
}