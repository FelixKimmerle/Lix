#include "CallExpr.hpp"
#include "VisitorExpr.hpp"

CallExpr::CallExpr(ExprPtr callee, TokenPosition position) : Expr(position),
                                                             callee(std::move(callee))
{
}

void CallExpr::visit(VisitorExpr *visitor)
{
    visitor->visitCall(this);
}

std::vector<ExprPtr>::iterator CallExpr::begin()
{
    return params.begin();
}
std::vector<ExprPtr>::iterator CallExpr::end()
{
    return params.end();
}

Expr *CallExpr::get_callee()
{
    return callee.get();
}

void CallExpr::add_param(ExprPtr param)
{
    params.push_back(std::move(param));
}