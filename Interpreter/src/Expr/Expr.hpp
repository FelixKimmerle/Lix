#pragma once
#include "LixTypenames.hpp"

#include <memory>

class VisitorExpr;
class Expr
{
protected:
    unsigned int m_uiLine;
public:
    Expr(unsigned int p_uiLine);
    virtual void visit(VisitorExpr *p_pVisitor) = 0;
    virtual unsigned int getLine();
};

typedef std::unique_ptr<Expr> ExprPtr;