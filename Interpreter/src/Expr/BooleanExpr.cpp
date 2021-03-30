
#include "BooleanExpr.hpp"
#include "VisitorExpr.hpp"

BooleanExpr::BooleanExpr(Lix_Bool p_Boolean, TokenPosition position) : Expr(position),
                                                                       boolean(p_Boolean)
{
}

void BooleanExpr::visit(VisitorExpr *visitor)
{
    visitor->visitBoolean(this);
}

Lix_Bool BooleanExpr::get_boolean()
{
    return boolean;
}
