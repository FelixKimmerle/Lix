#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class ForStmt : public Stmt
{
private:
	ExprPtr m_pCondition;
	StmtPtr m_pBody;
	StmtPtr m_pInitializer;
	ExprPtr m_pIncrement;

public:
	ForStmt(ExprPtr p_pCondition, StmtPtr p_pBody, StmtPtr p_pInitializer, ExprPtr p_pIncrement, unsigned int p_uiLine);
	Expr* getCondition();
	Stmt* getBody();
	Stmt* getInitializer();
	Expr* getIncrement();
	void visit(VisitorStmt *p_pVisitor);
};
