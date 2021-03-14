#pragma once
#include "Scanner.hpp"
#include "Expr/Expr.hpp"
#include "Stmt/Stmt.hpp"
#include <list>
#include "LixTypenames.hpp"
#include "Variable.hpp"
#include "Expr/VarExpr.hpp"
#include "Logger.hpp"
#include <memory>
#include "Stmt/BlockStmt.hpp"

class Parser
{
private:
    Scanner m_Scanner;
    bool match(const std::vector<Token::TokenType> &p_lTypes);
    bool match(const Token::TokenType &p_Type);
    bool check(const Token::TokenType &p_TokenType);
    bool checkNext(const Token::TokenType &p_TokenType);
    bool isAtEnd();
    Token peek();
    Token previous();
    Token advance();
    Token consume(Token::TokenType p_TokenType, const std::string &p_sMessage);
    LixDatatype tokenToDatatype(Token::TokenType p_TokenType);
    bool matchDatatype();

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> logicalor();
    std::unique_ptr<Expr> logicaland();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> addition();
    std::unique_ptr<Expr> multiplication();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> call();
    std::unique_ptr<Expr> finishCall(std::unique_ptr<Expr> callee);
    std::unique_ptr<Expr> literal();

    std::unique_ptr<BlockStmt> block();
    std::unique_ptr<Stmt> declaration();
    std::unique_ptr<Stmt> varDeclaration(LixDatatype type, Token name);
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> printStatement();
    std::unique_ptr<Stmt> ifStatement();
    std::unique_ptr<Stmt> whileStatement();
    std::unique_ptr<Stmt> forStatement();
    std::unique_ptr<Stmt> funDeclaration(LixDatatype type, Token name);
    std::unique_ptr<Stmt> returnStmt();


    std::unique_ptr<Stmt> expressionStatement();

    std::vector<Token> m_Tokens;
    std::vector<Token>::iterator m_Current;


    bool m_bHadError;
    bool m_bPanicMode;
    void error(Token *p_pToken, const std::string &p_sMessage);
    void synchronize();
    Logger *m_Logger;

public:
    Parser(std::string p_sSource,Logger *p_Logger);
    ~Parser();
    std::unique_ptr<BlockStmt> parse();
    bool hadError();
};
