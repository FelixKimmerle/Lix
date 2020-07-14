#pragma once

#include "Stmt/Stmt.hpp"
#include <vector>
#include "../LixTypenames.hpp"

class FuncDecl : public Stmt
{
private:
    std::vector<std::pair<LixDatatype, std::string>> m_vArgs;
    Stmt *m_Body;
    std::string m_sName;

public:
    FuncDecl(std::string p_sName,const std::vector<std::pair<LixDatatype, std::string>> p_vArgs, Stmt *p_Body, unsigned int p_uiLine);
    ~FuncDecl();
    void visit(VisitorStmt *p_pVisitor);
    Stmt *getBody();
    std::string getName();
    std::vector<std::pair<LixDatatype, std::string>>::iterator begin();
    std::vector<std::pair<LixDatatype, std::string>>::iterator end();
};
