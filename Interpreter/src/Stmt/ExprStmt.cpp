#include "Stmt/ExprStmt.hpp"
#include "Stmt/VisitorStmt.hpp"

ExprStmt::ExprStmt(ExprPtr p_pExpr, TokenPosition position) : expr(std::move(p_pExpr)),
                                                             Stmt(position)
{
}

void ExprStmt::visit(VisitorStmt *visitor)
{
    visitor->visitExprStmt(this);
}

Expr *ExprStmt::get_expr()
{
    return expr.get();
}