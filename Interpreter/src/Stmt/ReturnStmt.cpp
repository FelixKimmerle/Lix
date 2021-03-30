#include "ReturnStmt.hpp"
#include "VisitorStmt.hpp"
ReturnStmt::ReturnStmt(ExprPtr expr, TokenPosition position) : Stmt(position),
                                                               expr(std::move(expr))

{
}

Expr *ReturnStmt::get_expr()
{
    return expr.get();
}

void ReturnStmt::visit(VisitorStmt *visitor)
{
    visitor->visitReturnStmt(this);
}