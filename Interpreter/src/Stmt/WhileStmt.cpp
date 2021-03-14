#include "WhileStmt.hpp"
#include "VisitorStmt.hpp"

WhileStmt::WhileStmt(ExprPtr p_pCondition, StmtPtr p_pBody, unsigned int p_uiLine) : m_pCondition(std::move(p_pCondition)),
																					 m_pBody(std::move(p_pBody)),
																					 Stmt(p_uiLine)
{
}

Expr *WhileStmt::getCondition()
{
	return m_pCondition.get();
}

Stmt *WhileStmt::getBody()
{
	return m_pBody.get();
}

void WhileStmt::visit(VisitorStmt *p_pVisitor)
{
	p_pVisitor->visitWhile(this);
}
