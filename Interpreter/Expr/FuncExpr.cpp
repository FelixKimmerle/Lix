#include "FuncExpr.hpp"
#include "VisitorExpr.hpp"

FuncExpr::FuncExpr(std::string p_name, std::vector<Expr *> p_vParams, unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_vParams = p_vParams;
    name = p_name;
}

FuncExpr::~FuncExpr()
{
}
void FuncExpr::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitFunc(this);
}

std::vector<Expr *> *FuncExpr::get_params()
{
    return &m_vParams;
}
std::string FuncExpr::get_name()
{
    return name;
}