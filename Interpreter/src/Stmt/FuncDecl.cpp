#include "FuncDecl.hpp"
#include "VisitorStmt.hpp"
FuncDecl::FuncDecl(std::string name, LixDatatype return_type, const std::vector<std::pair<LixDatatype, std::string>> args,
                   std::unique_ptr<BlockStmt> body, TokenPosition position) : Stmt(position),
                                                                              body(std::move(body)),
                                                                              return_type(return_type),
                                                                              args(args),
                                                                              name(name)
{
}

void FuncDecl::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitFuncDecl(this);
}

BlockStmt *FuncDecl::get_body()
{
    return body.get();
}

std::string FuncDecl::get_name() const
{
    return name;
}

LixDatatype FuncDecl::get_return_type() const
{
    return return_type;
}

std::vector<std::pair<LixDatatype, std::string>>::iterator FuncDecl::begin()
{
    return args.begin();
}
std::vector<std::pair<LixDatatype, std::string>>::iterator FuncDecl::end()
{
    return args.end();
}

unsigned int FuncDecl::get_arity() const
{
    return args.size();
}