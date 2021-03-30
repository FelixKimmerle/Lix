#include "ExplicitCastExpr.hpp"
#include "VisitorExpr.hpp"
ExplicitCastExpr::ExplicitCastExpr(ExprPtr p_pExpr, LixDatatype p_Type, TokenPosition position) : Expr(position),
                                                                                                  expr(std::move(p_pExpr)),
                                                                                                  type(p_Type)

{
}

void ExplicitCastExpr::visit(VisitorExpr *visitor)
{
    visitor->visitExplicitCast(this);
}
Expr *ExplicitCastExpr::get_expr()
{
    return expr.get();
}
LixDatatype ExplicitCastExpr::get_type()
{
    return type;
}