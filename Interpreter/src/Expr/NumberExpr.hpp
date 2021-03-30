#pragma once
#include <string>
#include "Expr.hpp"
#include "LixTypenames.hpp"

template <class T>
class NumberExpr : public Expr
{
private:
    T number;
public:
    NumberExpr(T number, TokenPosition position);
    void visit(VisitorExpr *visitor);
    T get_number();
};
