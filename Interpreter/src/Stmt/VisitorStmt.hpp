#pragma once
#include "PrintStmt.hpp"
#include "BlockStmt.hpp"
#include "VarStmt.hpp"
#include "IfStmt.hpp"
#include "WhileStmt.hpp"
#include "ForStmt.hpp"
#include "ExprStmt.hpp"
#include "FuncDecl.hpp"
#include "ReturnStmt.hpp"
class VisitorStmt
{
private:
	/* data */
public:
	VisitorStmt(/* args */);
	virtual ~VisitorStmt();
	virtual void visitPrint(PrintStmt *p_pStmt) = 0;
	virtual void visitBlock(BlockStmt *p_pStmt) = 0;
	virtual void visitVar(VarStmt *p_pStmt) = 0;
	virtual void visitIf(IfStmt *p_pStmt) = 0;
	virtual void visitWhile(WhileStmt *p_pStmt) = 0;
	virtual void visitFor(ForStmt *p_pStmt) = 0;
	virtual void visitExprStmt(ExprStmt *p_pStmt) = 0;
	virtual void visitFuncDecl(FuncDecl *p_pStmt) = 0;
	virtual void visitReturnStmt(ReturnStmt *p_pStmt) = 0;
};
