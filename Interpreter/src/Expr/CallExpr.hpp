#pragma once
#include "Expr.hpp"
#include <vector>

class CallExpr : public Expr
{
private:
    ExprPtr callee;
    std::vector<ExprPtr> params;

public:
    CallExpr(ExprPtr callee, TokenPosition position);
    void visit(VisitorExpr *p_pVisitor);
    Expr *get_callee();
    void add_param(ExprPtr param);
    std::vector<ExprPtr>::iterator begin();
    std::vector<ExprPtr>::iterator end();
};
