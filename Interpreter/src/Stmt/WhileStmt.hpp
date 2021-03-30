#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class WhileStmt : public Stmt
{
private:
	ExprPtr condition;
	StmtPtr body;

public:
	WhileStmt(ExprPtr condition, StmtPtr body, TokenPosition position);
	void visit(VisitorStmt *visitor);
	Expr *get_condition();
	Stmt *get_body();
};
