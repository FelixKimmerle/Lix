#pragma once
#include <string>
#include "Expr.hpp"
#include "LixTypenames.hpp"

class BooleanExpr : public Expr
{
private:
    Lix_Bool m_Boolean;

public:
    BooleanExpr(Lix_Bool p_Boolean, unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Lix_Bool getBoolean();
};
