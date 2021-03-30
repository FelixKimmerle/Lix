#pragma once

#include "Stmt/Stmt.hpp"
#include "Expr/Expr.hpp"
#include "LixTypenames.hpp"
#include "Variable.hpp"
#include <string>

class VarStmt : public Stmt
{
private:
    ExprPtr initializer;
    LixDatatype type;
    std::string name;

public:
    VarStmt(std::string name, LixDatatype type, ExprPtr initializer, TokenPosition position);
    virtual void visit(VisitorStmt *visitor);
    Expr *get_initializer();
    LixDatatype get_type();
    std::string get_name();
};
