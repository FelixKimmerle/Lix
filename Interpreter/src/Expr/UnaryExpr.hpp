#pragma once

#include "Expr.hpp"

class UnaryExpr : public Expr
{
public:
    enum UnaryOperator
    {
        UO_MINUS,
        UO_BANG,
    };

private:
    ExprPtr expr;
    UnaryOperator unary_operator;

public:
    UnaryExpr(ExprPtr expr, UnaryOperator unary_operator, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Expr *get_expr();
    UnaryOperator get_unary_operator();
};
