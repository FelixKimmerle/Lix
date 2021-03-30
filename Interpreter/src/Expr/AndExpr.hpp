#pragma once
#include "Expr.hpp"

class AndExpr : public Expr
{
private:
    ExprPtr left;
    ExprPtr right;

public:
    AndExpr(ExprPtr left, ExprPtr right, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Expr *get_left();
    Expr *get_right();
};
