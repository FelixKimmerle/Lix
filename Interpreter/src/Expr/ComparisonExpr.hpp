#pragma once

#include "Expr.hpp"

class ComparisonExpr : public Expr
{
public:
    enum ComparisonOperator
    {
        BO_EQUAL,
        BO_LESS,
        BO_LESS_EQUAL,
        BO_GREATER,
        BO_GREATER_EQUAL,
    };

private:
    ExprPtr left;
    ExprPtr right;
    ComparisonOperator binary_operator;

public:
    ComparisonExpr(ExprPtr left, ExprPtr right, ComparisonOperator binary_operator, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Expr *get_left();
    Expr *get_right();
    ComparisonOperator get_binary_operator();
};
