#pragma once
#include "Expr.hpp"

class OrExpr : public Expr
{
private:
    ExprPtr left;
    ExprPtr right;

public:
    OrExpr(ExprPtr left, ExprPtr right, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Expr *get_left();
    Expr *get_right();
};

