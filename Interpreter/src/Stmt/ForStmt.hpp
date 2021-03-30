#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class ForStmt : public Stmt
{
private:
	ExprPtr condition;
	StmtPtr body;
	StmtPtr initializer;
	ExprPtr increment;

public:
	ForStmt(ExprPtr condition, StmtPtr body, StmtPtr initializer, ExprPtr increment, TokenPosition position);
	Expr* get_condition();
	Stmt* get_body();
	Stmt* get_initializer();
	Expr* get_increment();
	void visit(VisitorStmt *visitor);
};
