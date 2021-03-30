#pragma once

#include "Expr.hpp"

class VarExpr : public Expr
{

private:
    std::string name;
    
public:
    VarExpr(std::string name, TokenPosition position);
    void visit(VisitorExpr *visitor);
    std::string get_name();
};
