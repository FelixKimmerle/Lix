#pragma once
#include "LixTypenames.hpp"
#include "TokenPosition.hpp"

#include <memory>

class VisitorExpr;
class Expr
{
protected:
    TokenPosition position;

public:
    Expr(TokenPosition position);
    virtual void visit(VisitorExpr *p_pVisitor) = 0;
    virtual TokenPosition get_position();
};

typedef std::unique_ptr<Expr> ExprPtr;