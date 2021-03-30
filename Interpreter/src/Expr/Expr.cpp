#include "Expr.hpp"

Expr::Expr(TokenPosition position) : position(position)
{
}

TokenPosition Expr::get_position()
{
    return position;
}
