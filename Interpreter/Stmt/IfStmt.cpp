#include "IfStmt.hpp"
#include "VisitorStmt.hpp"
IfStmt::IfStmt(Expr* p_pCondition, Stmt* p_pThen, Stmt* p_pElse,unsigned int p_uiLine) : Stmt(p_uiLine)
{
	m_pCondition = p_pCondition;
	m_pThen = p_pThen;
	m_pElse = p_pElse;
}

IfStmt::~IfStmt()
{
	delete m_pCondition;
	delete m_pThen;
	if (m_pElse != nullptr)
	{
		delete m_pElse;
	}

}

void IfStmt::visit(VisitorStmt* p_pVisitor)
{
	p_pVisitor->visitIf(this);
}

Expr* IfStmt::getCondition()
{
	return m_pCondition;
}

Stmt* IfStmt::getThen()
{
	return m_pThen;
}

Stmt* IfStmt::getElse()
{
	return m_pElse;
}
