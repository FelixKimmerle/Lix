#pragma once

#include "Stmt/Stmt.hpp"
#include <vector>
#include "../LixTypenames.hpp"
#include "BlockStmt.hpp"

class FuncDecl : public Stmt
{
private:
    std::vector<std::pair<LixDatatype, std::string>> args;
    std::unique_ptr<BlockStmt> body;
    std::string name;
    LixDatatype return_type;

public:
    FuncDecl(std::string name, LixDatatype return_type, const std::vector<std::pair<LixDatatype, std::string>> args, std::unique_ptr<BlockStmt> body, TokenPosition position);
    void visit(VisitorStmt *visitor);
    BlockStmt *get_body();
    std::string get_name() const;
    LixDatatype get_return_type() const;
    std::vector<std::pair<LixDatatype, std::string>>::iterator begin();
    std::vector<std::pair<LixDatatype, std::string>>::iterator end();
    unsigned int get_arity() const;
};
