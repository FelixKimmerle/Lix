#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class ForStmt : public Stmt
{
private:
	Expr* m_pCondition;
	Stmt* m_pBody;
	Stmt* m_pInitializer;
	Expr* m_pIncrement;

public:
	ForStmt(Expr* p_pCondition, Stmt* p_pBody, Stmt* p_pInitializer, Expr* p_pIncrement, unsigned int p_uiLine);
	~ForStmt();
	Expr* getCondition();
	Stmt* getBody();
	Stmt* getInitializer();
	Expr* getIncrement();
	void visit(VisitorStmt* p_pVisitor);
};

