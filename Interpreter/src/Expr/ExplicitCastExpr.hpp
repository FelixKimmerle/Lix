#pragma once

#include "Expr.hpp"
#include "LixTypenames.hpp"

class ExplicitCastExpr : public Expr
{
private:
    ExprPtr m_pExpr;
    LixDatatype m_to;
public:
    ExplicitCastExpr(ExprPtr p_pExpr, LixDatatype p_Type,unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Expr * getExpr();
    LixDatatype getTo();
};

