#include "GroupingExpr.hpp"
#include "VisitorExpr.hpp"

GroupingExpr::GroupingExpr(ExprPtr p_pExpr, TokenPosition position) : Expr(position),
                                                                      expr(std::move(p_pExpr))

{
}

void GroupingExpr::visit(VisitorExpr *visitor)
{
    visitor->visitGrouping(this);
}

Expr *GroupingExpr::get_expr()
{
    return expr.get();
}
