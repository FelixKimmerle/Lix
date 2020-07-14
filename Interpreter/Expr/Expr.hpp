#pragma once
#include "LixTypenames.hpp"
class VisitorExpr;
class Expr
{
protected:
    unsigned int m_uiLine;
public:
    Expr(unsigned int p_uiLine);
    virtual ~Expr();
    virtual void visit(VisitorExpr *p_pVisitor) = 0;
    virtual unsigned int getLine();
};
