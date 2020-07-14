#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class WhileStmt : public Stmt
{
private:
	Expr *m_pCondition;
	Stmt *m_pBody;

public:
	WhileStmt(Expr *p_pCondition, Stmt *p_pBody, unsigned int p_uiLine);
	~WhileStmt();
	Expr *getCondition();
	Stmt *getBody();
	void visit(VisitorStmt *p_pVisitor);
};
