#pragma once
#include <string>
#include "Expr.hpp"
#include "LixTypenames.hpp"

template <class T>
class NumberExpr : public Expr
{
private:
    T m_Number;
public:
    NumberExpr(T p_Number, unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    T getNumber();
};
