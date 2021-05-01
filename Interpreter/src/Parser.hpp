#pragma once

#include "Scanner.hpp"
#include "Expr/Expr.hpp"
#include "Expr/VarExpr.hpp"
#include "Stmt/Stmt.hpp"
#include "Stmt/BlockStmt.hpp"
#include "LixTypenames.hpp"
#include "Variable.hpp"
#include "Logger.hpp"

#include <list>
#include <memory>

class Parser
{
private:
    Scanner scanner;
    bool match(const std::vector<Token::TokenType> &types);
    bool match(const Token::TokenType &type);
    bool check(const Token::TokenType &token_type);
    bool check_next(const Token::TokenType &token_type);
    bool is_at_end();
    Token advance();
    Token consume(Token::TokenType token_type, const std::string &message);
    LixDatatype token_to_datatype(Token::TokenType token_type);
    bool match_datatype();

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> logicalor();
    std::unique_ptr<Expr> logicaland();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> addition();
    std::unique_ptr<Expr> multiplication();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> call();
    std::unique_ptr<Expr> finish_call(std::unique_ptr<Expr> callee);
    std::unique_ptr<Expr> literal();

    std::unique_ptr<BlockStmt> block();
    std::unique_ptr<Stmt> declaration();
    std::unique_ptr<Stmt> var_declaration(LixDatatype type, Token name);
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> print_statement();
    std::unique_ptr<Stmt> if_statement();
    std::unique_ptr<Stmt> while_statement();
    std::unique_ptr<Stmt> for_statement();
    std::unique_ptr<Stmt> fun_declaration(LixDatatype type, Token name);
    std::unique_ptr<Stmt> return_stmt();
    std::unique_ptr<Stmt> expression_statement();

    Token current;
    Token last;

    bool had_error;
    bool panic_mode;
    void error(const Token &token, const std::string &message);
    void synchronize();
    Logger *logger;

public:
    Parser(std::string source, Logger *logger);
    std::unique_ptr<BlockStmt> parse();
    bool hadError();
};
