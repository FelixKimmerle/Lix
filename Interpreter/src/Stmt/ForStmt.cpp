#include "ForStmt.hpp"
#include "VisitorStmt.hpp"

ForStmt::ForStmt(ExprPtr p_pCondition, StmtPtr p_pBody, StmtPtr p_pInitializer, ExprPtr p_pIncrement, unsigned int p_uiLine) : Stmt(p_uiLine),
																															   m_pBody(std::move(p_pBody)),
																															   m_pCondition(std::move(p_pCondition)),
																															   m_pInitializer(std::move(p_pInitializer)),
																															   m_pIncrement(std::move(p_pIncrement))
{
}

Expr *ForStmt::getCondition()
{
	return m_pCondition.get();
}

Stmt *ForStmt::getBody()
{
	return m_pBody.get();
}

Stmt *ForStmt::getInitializer()
{
	return m_pInitializer.get();
}

Expr *ForStmt::getIncrement()
{
	return m_pIncrement.get();
}

void ForStmt::visit(VisitorStmt *p_pVisitor)
{
	p_pVisitor->visitFor(this);
}
