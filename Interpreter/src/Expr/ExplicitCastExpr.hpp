#pragma once

#include "Expr.hpp"
#include "LixTypenames.hpp"

class ExplicitCastExpr : public Expr
{
private:
    ExprPtr expr;
    LixDatatype type;
public:
    ExplicitCastExpr(ExprPtr expr, LixDatatype type, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Expr * get_expr();
    LixDatatype get_type();
};

