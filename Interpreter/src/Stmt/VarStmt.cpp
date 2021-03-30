#include "VarStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
VarStmt::VarStmt(std::string name, LixDatatype type, ExprPtr initializer, TokenPosition position) : Stmt(position),
                                                                                                    initializer(std::move(initializer)),
                                                                                                    type(type),
                                                                                                    name(name)

{
}

void VarStmt::visit(VisitorStmt *visitor)
{
    visitor->visitVar(this);
}

Expr *VarStmt::get_initializer()
{
    return initializer.get();
}

LixDatatype VarStmt::get_type()
{
    return type;
}

std::string VarStmt::get_name()
{
    return name;
}