#include "ForStmt.hpp"
#include "VisitorStmt.hpp"

ForStmt::ForStmt(Expr *p_pCondition, Stmt *p_pBody, Stmt *p_pInitializer, Expr *p_pIncrement, unsigned int p_uiLine) : Stmt(p_uiLine)
{
	m_pBody = p_pBody;
	m_pCondition = p_pCondition;
	m_pInitializer = p_pInitializer;
	m_pIncrement = p_pIncrement;
}

ForStmt::~ForStmt()
{
	delete m_pBody;
	if (m_pCondition != nullptr)
	{
		delete m_pCondition;
	}
	if (m_pIncrement != nullptr)
	{
		delete m_pIncrement;
	}
	if (m_pInitializer != nullptr)
	{
		delete m_pInitializer;
	}
}

Expr *ForStmt::getCondition()
{
	return m_pCondition;
}

Stmt *ForStmt::getBody()
{
	return m_pBody;
}

Stmt *ForStmt::getInitializer()
{
	return m_pInitializer;
}

Expr *ForStmt::getIncrement()
{
	return m_pIncrement;
}

void ForStmt::visit(VisitorStmt *p_pVisitor)
{
	p_pVisitor->visitFor(this);
}
