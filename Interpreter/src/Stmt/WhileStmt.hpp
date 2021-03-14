#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class WhileStmt : public Stmt
{
private:
	ExprPtr m_pCondition;
	StmtPtr m_pBody;

public:
	WhileStmt(ExprPtr p_pCondition, StmtPtr p_pBody, unsigned int p_uiLine);
	Expr *getCondition();
	Stmt *getBody();
	void visit(VisitorStmt *p_pVisitor);
};
