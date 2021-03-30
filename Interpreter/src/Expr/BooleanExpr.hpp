#pragma once
#include <string>
#include "Expr.hpp"
#include "LixTypenames.hpp"

class BooleanExpr : public Expr
{
private:
    Lix_Bool boolean;

public:
    BooleanExpr(Lix_Bool boolean, TokenPosition position);
    void visit(VisitorExpr *visitor);
    Lix_Bool get_boolean();
};
