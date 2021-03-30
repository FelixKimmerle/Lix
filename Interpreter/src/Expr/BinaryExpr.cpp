#include "BinaryExpr.hpp"
#include "VisitorExpr.hpp"

BinaryExpr::BinaryExpr(ExprPtr left, ExprPtr right, BinaryExpr::BinaryOperator binary_operator, TokenPosition position) : Expr(position),
                                                                                                                          left(std::move(left)),
                                                                                                                          right(std::move(right)),
                                                                                                                          binary_operator(binary_operator)

{
}

void BinaryExpr::visit(VisitorExpr *visitor)
{
    visitor->visitBinary(this);
}

Expr *BinaryExpr::get_left()
{
    return left.get();
}
Expr *BinaryExpr::get_right()
{
    return right.get();
}
BinaryExpr::BinaryOperator BinaryExpr::get_binary_operator()
{
    return binary_operator;
}
