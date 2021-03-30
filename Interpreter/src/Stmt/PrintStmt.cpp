#include "Stmt/PrintStmt.hpp"
#include "Stmt/VisitorStmt.hpp"

PrintStmt::PrintStmt(ExprPtr expr, TokenPosition position) : Stmt(position),
                                                             expr(std::move(expr))

{
}

void PrintStmt::visit(VisitorStmt *visitor)
{
    visitor->visitPrint(this);
}

Expr *PrintStmt::get_expr()
{
    return expr.get();
}