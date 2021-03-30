#pragma once

#include "Expr.hpp"

class BinaryExpr : public Expr
{
public:
    enum BinaryOperator
    {
        BO_ADD,
        BO_SUB,
        BO_MUL,
        BO_DIV,
    };

private:
    ExprPtr left;
    ExprPtr right;
    BinaryOperator binary_operator;

public:
    BinaryExpr(ExprPtr left, ExprPtr right, BinaryExpr::BinaryOperator binary_operator, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Expr *get_left();
    Expr *get_right();
    BinaryOperator get_binary_operator();
};
