#include "WhileStmt.hpp"
#include "VisitorStmt.hpp"

WhileStmt::WhileStmt(ExprPtr condition, StmtPtr body, TokenPosition position) : Stmt(position),
																				condition(std::move(condition)),
																				body(std::move(body))

{
}

Expr *WhileStmt::get_condition()
{
	return condition.get();
}

Stmt *WhileStmt::get_body()
{
	return body.get();
}

void WhileStmt::visit(VisitorStmt *visitor)
{
	visitor->visitWhile(this);
}
