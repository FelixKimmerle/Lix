#include "IfStmt.hpp"
#include "VisitorStmt.hpp"
IfStmt::IfStmt(ExprPtr condition, StmtPtr then_body, StmtPtr else_body, TokenPosition position) : Stmt(position),
																								  condition(std::move(condition)),
																								  then_body(std::move(then_body)),
																								  else_body(std::move(else_body))

{
}

void IfStmt::visit(VisitorStmt *visitor)
{
	visitor->visitIf(this);
}

Expr *IfStmt::get_condition()
{
	return condition.get();
}

Stmt *IfStmt::get_then()
{
	return then_body.get();
}

Stmt *IfStmt::get_else()
{
	return else_body.get();
}
