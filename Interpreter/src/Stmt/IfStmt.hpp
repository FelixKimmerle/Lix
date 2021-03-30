#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class IfStmt : public Stmt
{
private:
	ExprPtr condition;
	StmtPtr then_body;
	StmtPtr else_body;

public:
	IfStmt(ExprPtr condition, StmtPtr then_body, StmtPtr else_body, TokenPosition position);
	void visit(VisitorStmt *visitor);
	Expr *get_condition();
	Stmt *get_then();
	Stmt *get_else();
};
