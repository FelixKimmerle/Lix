#pragma once

#include "Expr.hpp"
#include "LixTypenames.hpp"

class ExplicitCastExpr : public Expr
{
private:
    Expr *m_pExpr;
    LixDatatype m_to;
public:
    ExplicitCastExpr(Expr *p_pExpr, LixDatatype p_Type,unsigned int p_uiLine);
    virtual ~ExplicitCastExpr();
    void visit(VisitorExpr *p_pVisitor);
    Expr * getExpr();
    LixDatatype getTo();
};

