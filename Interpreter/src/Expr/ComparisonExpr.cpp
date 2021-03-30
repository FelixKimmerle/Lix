#include "ComparisonExpr.hpp"
#include "VisitorExpr.hpp"

ComparisonExpr::ComparisonExpr(ExprPtr p_pLeft, ExprPtr p_pRight, ComparisonExpr::ComparisonOperator p_BinaryOperator, TokenPosition position) : Expr(position),
                                                                                                                                                 left(std::move(p_pLeft)),
                                                                                                                                                 right(std::move(p_pRight)),
                                                                                                                                                 binary_operator(p_BinaryOperator)

{
}

void ComparisonExpr::visit(VisitorExpr *visitor)
{
    visitor->visitComparison(this);
}

Expr *ComparisonExpr::get_left()
{
    return left.get();
}
Expr *ComparisonExpr::get_right()
{
    return right.get();
}
ComparisonExpr::ComparisonOperator ComparisonExpr::get_binary_operator()
{
    return binary_operator;
}
