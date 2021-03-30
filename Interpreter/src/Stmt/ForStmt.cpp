#include "ForStmt.hpp"
#include "VisitorStmt.hpp"

ForStmt::ForStmt(ExprPtr condition, StmtPtr body, StmtPtr initializer, ExprPtr increment, TokenPosition position) : Stmt(position),
																															   body(std::move(body)),
																															   condition(std::move(condition)),
																															   initializer(std::move(initializer)),
																															   increment(std::move(increment))
{
}

Expr *ForStmt::get_condition()
{
	return condition.get();
}

Stmt *ForStmt::get_body()
{
	return body.get();
}

Stmt *ForStmt::get_initializer()
{
	return initializer.get();
}

Expr *ForStmt::get_increment()
{
	return increment.get();
}

void ForStmt::visit(VisitorStmt *visitor)
{
	visitor->visitFor(this);
}
