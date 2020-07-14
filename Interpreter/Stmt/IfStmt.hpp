#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class IfStmt : public Stmt
{
private:
	Expr *m_pCondition;
	Stmt *m_pThen;
	Stmt *m_pElse;

public:
	IfStmt(Expr *p_pCondition, Stmt *p_pThen, Stmt *p_pElse, unsigned int p_uiLine);
	~IfStmt();
	void visit(VisitorStmt *p_pVisitor);
	Expr *getCondition();
	Stmt *getThen();
	Stmt *getElse();
};
