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
public:
	virtual void visitPrint(PrintStmt *print_stmt) = 0;
	virtual void visitBlock(BlockStmt *block_stmt) = 0;
	virtual void visitVar(VarStmt *var_stmt) = 0;
	virtual void visitIf(IfStmt *if_stmt) = 0;
	virtual void visitWhile(WhileStmt *while_stmt) = 0;
	virtual void visitFor(ForStmt *for_stmt) = 0;
	virtual void visitExprStmt(ExprStmt *expr_stmt) = 0;
	virtual void visitFuncDecl(FuncDecl *func_decl_stmt) = 0;
	virtual void visitReturnStmt(ReturnStmt *return_stmt) = 0;
};
