#pragma once

#include "Stmt/Stmt.hpp"
#include <vector>
#include "../LixTypenames.hpp"
#include "BlockStmt.hpp"

class FuncDecl : public Stmt
{
private:
    std::vector<std::pair<LixDatatype, std::string>> m_vArgs;
    std::unique_ptr<BlockStmt> m_Body;
    std::string m_sName;
    LixDatatype return_type;

public:
    FuncDecl(std::string p_sName, LixDatatype p_return_type, const std::vector<std::pair<LixDatatype, std::string>> p_vArgs, std::unique_ptr<BlockStmt> p_Body, unsigned int p_uiLine);
    void visit(VisitorStmt *p_pVisitor);
    BlockStmt *getBody();
    std::string getName() const;
    LixDatatype get_return_type() const;
    std::vector<std::pair<LixDatatype, std::string>>::iterator begin();
    std::vector<std::pair<LixDatatype, std::string>>::iterator end();
    unsigned int get_arity() const;
};
