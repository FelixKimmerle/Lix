#pragma once
#include "Expr.hpp"
#include <vector>

class CallExpr : public Expr
{
private:
    std::vector<ExprPtr> m_vParams;
    ExprPtr callee;

public:
    CallExpr(ExprPtr callee, unsigned int p_uiLine);
    void visit(VisitorExpr *p_pVisitor);
    Expr *get_callee();
    void add_param(ExprPtr param);
    std::vector<ExprPtr>::iterator begin();
    std::vector<ExprPtr>::iterator end();
};
