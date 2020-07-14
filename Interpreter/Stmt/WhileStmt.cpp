#include "WhileStmt.hpp"
#include "VisitorStmt.hpp"

WhileStmt::WhileStmt(Expr *p_pCondition, Stmt *p_pBody, unsigned int p_uiLine) : Stmt(p_uiLine)
{
	m_pBody = p_pBody;
	m_pCondition = p_pCondition;
}

WhileStmt::~WhileStmt()
{
	delete m_pCondition;
	delete m_pBody;
}

Expr *WhileStmt::getCondition()
{
	return m_pCondition;
}

Stmt *WhileStmt::getBody()
{
	return m_pBody;
}

void WhileStmt::visit(VisitorStmt *p_pVisitor)
{
	p_pVisitor->visitWhile(this);
}
