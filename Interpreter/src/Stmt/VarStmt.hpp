#pragma once

#include "Stmt/Stmt.hpp"
#include "Expr/Expr.hpp"
#include "LixTypenames.hpp"
#include "Variable.hpp"
#include <string>

class VarStmt : public Stmt
{
private:
    ExprPtr m_Initializer;
    LixDatatype m_Type;
    std::string m_sName;

public:
    VarStmt(std::string p_sName, LixDatatype p_Type, ExprPtr p_Initializer, unsigned int p_uiLine);
    virtual void visit(VisitorStmt *p_pVisitor);
    Expr *getInitializer();
    LixDatatype getType();
    std::string getName();
};
