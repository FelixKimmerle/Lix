#include "FuncDecl.hpp"
#include "VisitorStmt.hpp"
FuncDecl::FuncDecl(std::string p_sName, LixDatatype p_return_type, const std::vector<std::pair<LixDatatype, std::string>> p_vArgs,
                   std::unique_ptr<BlockStmt> p_Body, unsigned int p_uiLine) : m_Body(std::move(p_Body)),
                                                                               Stmt(p_uiLine),
                                                                               return_type(p_return_type)
{
    m_vArgs = p_vArgs;
    m_sName = p_sName;
}

void FuncDecl::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitFuncDecl(this);
}

BlockStmt *FuncDecl::getBody()
{
    return m_Body.get();
}

std::string FuncDecl::getName() const
{
    return m_sName;
}

LixDatatype FuncDecl::get_return_type() const
{
    return return_type;
}

std::vector<std::pair<LixDatatype, std::string>>::iterator FuncDecl::begin()
{
    return m_vArgs.begin();
}
std::vector<std::pair<LixDatatype, std::string>>::iterator FuncDecl::end()
{
    return m_vArgs.end();
}

unsigned int FuncDecl::get_arity() const
{
    return m_vArgs.size();
}