#include "IfStmt.hpp"
#include "VisitorStmt.hpp"
IfStmt::IfStmt(ExprPtr p_pCondition, StmtPtr p_pThen, StmtPtr p_pElse, unsigned int p_uiLine) : m_pCondition(std::move(p_pCondition)),
																								m_pThen(std::move(p_pThen)),
																								m_pElse(std::move(p_pElse)),
																								Stmt(p_uiLine)
{
}

void IfStmt::visit(VisitorStmt *p_pVisitor)
{
	p_pVisitor->visitIf(this);
}

Expr *IfStmt::getCondition()
{
	return m_pCondition.get();
}

Stmt *IfStmt::getThen()
{
	return m_pThen.get();
}

Stmt *IfStmt::getElse()
{
	return m_pElse.get();
}
