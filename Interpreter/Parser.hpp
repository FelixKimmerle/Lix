#pragma once
#include "Scanner.hpp"
#include "Expr/Expr.hpp"
#include "Stmt/Stmt.hpp"
#include <list>
#include "LixTypenames.hpp"
#include "Variable.hpp"
#include "Expr/VarExpr.hpp"
#include "Logger.hpp"

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

    Expr *expression();
    Expr *logicalor();
    Expr *logicaland();
    Expr *equality();
    Expr *comparison();
    Expr *addition();
    Expr *multiplication();
    Expr *unary();
    Expr *literal();

    Stmt *block();
    Stmt *declaration();
    Stmt *varDeclaration(LixDatatype type, Token name);
    Stmt *statement();
    Stmt *printStatement();
    Stmt *ifStatement();
    Stmt *whileStatement();
    Stmt *forStatement();
    Stmt *funDeclaration(LixDatatype type, Token name);
    Stmt *returnStmt();


    Stmt *expressionStatement();

    std::vector<Token> m_Tokens;
    std::vector<Token>::iterator m_Current;


    bool m_bHadError;
    bool m_bPanicMode;
    void error(Token *p_pToken, const std::string &p_sMessage);
    void synchronize();
    Logger *m_Logger;

public:
    Parser(std::string p_sSource,Logger *p_Logger);
    virtual ~Parser();
    std::vector<Stmt *> parse();
    bool hadError();
};
