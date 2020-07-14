#include "FuncDecl.hpp"
#include "VisitorStmt.hpp"
FuncDecl::FuncDecl(std::string p_sName, const std::vector<std::pair<LixDatatype, std::string>> p_vArgs,
                   Stmt *p_Body, unsigned int p_uiLine) : Stmt(p_uiLine)
{
    m_Body = p_Body;
    m_vArgs = p_vArgs;
    m_sName = p_sName;
}

FuncDecl::~FuncDecl()
{
    delete m_Body;
}

void FuncDecl::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitFuncDecl(this);
}

Stmt *FuncDecl::getBody()
{
    return m_Body;
}

std::string FuncDecl::getName()
{
    return m_sName;
}

std::vector<std::pair<LixDatatype, std::string>>::iterator FuncDecl::begin()
{
    return m_vArgs.begin();
}
std::vector<std::pair<LixDatatype, std::string>>::iterator FuncDecl::end()
{
    return m_vArgs.end();
}