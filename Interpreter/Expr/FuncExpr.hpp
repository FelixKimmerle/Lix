#pragma once
#include "Expr.hpp"
#include <vector>

class FuncExpr : public Expr
{
private:
    std::vector<Expr *> m_vParams;
    std::string name;

public:
    FuncExpr(std::string p_name, std::vector<Expr *> p_vParams, unsigned int p_uiLine);
    ~FuncExpr();
    void visit(VisitorExpr *p_pVisitor);
    std::vector<Expr *> *get_params();
    std::string get_name();
};
