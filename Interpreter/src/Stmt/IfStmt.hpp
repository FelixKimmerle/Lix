#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class IfStmt : public Stmt
{
private:
	ExprPtr m_pCondition;
	StmtPtr m_pThen;
	StmtPtr m_pElse;

public:
	IfStmt(ExprPtr p_pCondition, StmtPtr p_pThen, StmtPtr p_pElse, unsigned int p_uiLine);
	void visit(VisitorStmt *p_pVisitor);
	Expr *getCondition();
	Stmt *getThen();
	Stmt *getElse();
};
