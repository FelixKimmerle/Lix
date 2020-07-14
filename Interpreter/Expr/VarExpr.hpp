#pragma once

#include "Expr.hpp"

class VarExpr : public Expr
{

private:
    std::string m_sName;
    
public:
    VarExpr(std::string p_sName, unsigned int p_uiLine);
    virtual ~VarExpr();
    void visit(VisitorExpr *p_pVisitor);
    std::string getName();
};
