#include "Parser.hpp"
#include "Expr/BinaryExpr.hpp"
#include "Expr/UnaryExpr.hpp"
#include "Expr/NumberExpr.hpp"
#include "Expr/BooleanExpr.hpp"
#include "Expr/GroupingExpr.hpp"
#include "Expr/ExplicitCastExpr.hpp"
#include "Expr/VarExpr.hpp"
#include "Expr/AssignExpr.hpp"
#include "Expr/OrExpr.hpp"
#include "Expr/AndExpr.hpp"
#include "Expr/ComparisonExpr.hpp"
#include "Expr/FuncExpr.hpp"

#include "Stmt/BlockStmt.hpp"
#include "Stmt/PrintStmt.hpp"
#include "Stmt/VarStmt.hpp"
#include "Stmt/IfStmt.hpp"
#include "Stmt/ForStmt.hpp"
#include "Stmt/WhileStmt.hpp"
#include "Stmt/ExprStmt.hpp"
#include "Stmt/FuncDecl.hpp"
#include "Stmt/ReturnStmt.hpp"

#include <iostream>
Parser::Parser(std::string p_sSource, Logger *p_Logger) : m_Scanner(p_sSource), m_bHadError(false), m_Logger(p_Logger), m_bPanicMode(false)
{
}

Parser::~Parser()
{
}

bool Parser::match(const std::vector<Token::TokenType> &p_lTypes)
{
	for (auto &&type : p_lTypes)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}
	return false;
}
bool Parser::match(const Token::TokenType &p_Type)
{
	if (check(p_Type))
	{
		advance();
		return true;
	}
	return false;
}
bool Parser::check(const Token::TokenType &p_TokenType)
{
	if (isAtEnd())
	{
		return false;
	}
	return peek().getType() == p_TokenType;
}
bool Parser::checkNext(const Token::TokenType &p_TokenType)
{
	if (isAtEnd())
	{
		return false;
	}
	if ((m_Current - 1)->getType() == Token::TokenType::TOKEN_EOF)
	{
		return false;
	}
	return (m_Current - 1)->getType() == p_TokenType;
}
bool Parser::isAtEnd()
{
	return m_Current->getType() == Token::TokenType::TOKEN_EOF;
}
Token Parser::peek()
{
	return *m_Current;
}
Token Parser::previous()
{
	return *(m_Current - 1);
}
Token Parser::advance()
{
	if (!isAtEnd())
	{
		m_Current++;
	}
	return previous();
}
Token Parser::consume(Token::TokenType p_TokenType, const std::string &p_sMessage)
{
	if (check(p_TokenType))
	{
		return advance();
	}
	error(&*m_Current, p_sMessage);
	return *m_Current;
}

LixDatatype Parser::tokenToDatatype(Token::TokenType p_TokenType)
{
	switch (p_TokenType)
	{
	case Token::TokenType::TOKEN_BOOL:
		return LixDatatype::LD_Bool;
	case Token::TokenType::TOKEN_INT:
		return LixDatatype::LD_Int;
	case Token::TokenType::TOKEN_FLOAT:
		return LixDatatype::LD_Float;
	case Token::TokenType::TOKEN_LONG:
		return LixDatatype::LD_LongInt;
	case Token::TokenType::TOKEN_DOUBLE:
		return LixDatatype::LD_Double;
	case Token::TokenType::TOKEN_BYTE:
		return LixDatatype::LD_Byte;
	case Token::TokenType::TOKEN_SHORT:
		return LixDatatype::LD_ShortInt;

	default:
		std::cout << "Token is not a datatype!" << std::endl;
		break;
	}
}

bool Parser::matchDatatype()
{
	return match({Token::TokenType::TOKEN_BOOL,
				  Token::TokenType::TOKEN_BYTE,
				  Token::TokenType::TOKEN_INT,
				  Token::TokenType::TOKEN_SHORT,
				  Token::TokenType::TOKEN_FLOAT,
				  Token::TokenType::TOKEN_DOUBLE,
				  Token::TokenType::TOKEN_LONG});
}

Expr *Parser::expression()
{
	Expr *expr = logicalor();

	return expr;
}

Expr *Parser::logicalor()
{
	Expr *expr = logicaland();

	while (match(Token::TokenType::TOKEN_OR))
	{
		Expr *right = logicaland();

		expr = new OrExpr(expr, right, previous().getLine());
	}
	return expr;
}
Expr *Parser::logicaland()
{
	Expr *expr = equality();

	while (match(Token::TokenType::TOKEN_AND))
	{
		Expr *right = equality();

		expr = new AndExpr(expr, right, previous().getLine());
	}
	return expr;
}
Expr *Parser::equality()
{
	Expr *expr = comparison();

	while (match({Token::TokenType::TOKEN_BANG_EQUAL, Token::TokenType::TOKEN_EQUAL_EQUAL}))
	{
		Token op = previous();
		Expr *right = comparison();

		if (op.getType() == Token::TokenType::TOKEN_EQUAL_EQUAL)
		{
			expr = new ComparisonExpr(expr, right, ComparisonExpr::ComparisonOperator::BO_EQUAL, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_BANG_EQUAL)
		{
			expr = new UnaryExpr(new ComparisonExpr(expr, right,
													ComparisonExpr::ComparisonOperator::BO_EQUAL, op.getLine()),
								 UnaryExpr::UnaryOperator::UO_BANG, op.getLine());
		}
	}
	return expr;
}
Expr *Parser::comparison()
{
	Expr *expr = addition();

	while (match({Token::TokenType::TOKEN_GREATER,
				  Token::TokenType::TOKEN_GREATER_EQUAL,
				  Token::TokenType::TOKEN_LESS,
				  Token::TokenType::TOKEN_LESS_EQUAL}))
	{
		Token op = previous();
		Expr *right = addition();

		if (op.getType() == Token::TokenType::TOKEN_GREATER)
		{
			expr = new ComparisonExpr(expr, right, ComparisonExpr::ComparisonOperator::BO_GREATER, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_LESS)
		{
			expr = new ComparisonExpr(expr, right, ComparisonExpr::ComparisonOperator::BO_LESS, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_GREATER_EQUAL)
		{
			expr = new ComparisonExpr(expr, right, ComparisonExpr::ComparisonOperator::BO_GREATER_EQUAL, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_LESS_EQUAL)
		{
			expr = new ComparisonExpr(expr, right, ComparisonExpr::ComparisonOperator::BO_LESS_EQUAL, op.getLine());
		}
	}
	return expr;
}

Expr *Parser::addition()
{
	Expr *expr = multiplication();

	while (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_PLUS}))
	{
		Token op = previous();
		Expr *right = addition();

		if (op.getType() == Token::TokenType::TOKEN_MINUS)
		{
			expr = new BinaryExpr(expr, right, BinaryExpr::BO_SUB, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_PLUS)
		{
			expr = new BinaryExpr(expr, right, BinaryExpr::BO_ADD, op.getLine());
		}
	}

	return expr;
}
Expr *Parser::multiplication()
{
	Expr *expr = unary();

	while (match({Token::TokenType::TOKEN_SLASH, Token::TokenType::TOKEN_STAR}))
	{
		Token op = previous();
		Expr *right = unary();

		if (op.getType() == Token::TokenType::TOKEN_SLASH)
		{
			expr = new BinaryExpr(expr, right, BinaryExpr::BO_DIV, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_STAR)
		{
			expr = new BinaryExpr(expr, right, BinaryExpr::BO_MUL, op.getLine());
		}
	}

	return expr;
}
Expr *Parser::unary()
{
	if (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_BANG}) || matchDatatype())
	{
		Token op = previous();
		if (op.getType() == Token::TokenType::TOKEN_MINUS)
		{
			return new UnaryExpr(unary(), UnaryExpr::UO_MINUS, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_BANG)
		{
			return new UnaryExpr(unary(), UnaryExpr::UO_BANG, op.getLine());
		}
		else
		{
			consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' between cast and expression.");
			Expr *right = unary();
			consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after cast.");
			return new ExplicitCastExpr(right, tokenToDatatype(op.getType()), op.getLine());
		}
	}

	return literal();
}
Expr *Parser::literal()
{
	if (match(Token::TokenType::TOKEN_FALSE))
	{
		return new BooleanExpr(false, previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_TRUE))
	{
		return new BooleanExpr(true, previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_BYTE))
	{
		return new NumberExpr<Lix_Byte>(static_cast<Lix_Byte>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_SHORT))
	{
		return new NumberExpr<Lix_ShortInt>(static_cast<Lix_ShortInt>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_INT))
	{
		return new NumberExpr<Lix_Int>(static_cast<Lix_Int>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_FLOAT))
	{
		return new NumberExpr<Lix_Float>(static_cast<Lix_Float>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_DOUBLE))
	{
		return new NumberExpr<Lix_Double>(static_cast<Lix_Double>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_LONG))
	{
		return new NumberExpr<Lix_LongInt>(static_cast<Lix_LongInt>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_LEFT_PAREN))
	{
		Expr *expr = expression();
		consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
		return new GroupingExpr(expr, expr->getLine());
	}
	if (match(Token::TokenType::TOKEN_IDENTIFIER))
	{
		Token name = previous();
		if (match(Token::TokenType::TOKEN_EQUAL))
		{
			VarExpr *var = new VarExpr(name.getLexeme(), name.getLine());
			Expr *assignexpr = expression();
			/*
			if (assignexpr->resultingType() != var->resultingType())
			{
				error(&name, "Type of variable: " + name.getLexeme() + " (" + lixDatatypeToString(var->resultingType()) + ") and assignment: (" + lixDatatypeToString(assignexpr->resultingType()) + ") does not match.");
			}
			*/
			return new AssignExpr(var, assignexpr, name.getLine());
		}
		if (match(Token::TokenType::TOKEN_LEFT_PAREN))
		{
			std::vector<Expr *> args;
			if (!match(Token::TokenType::TOKEN_RIGHT_PAREN))
			{
				do
				{
					args.push_back(expression());
				} while (match(Token::TokenType::TOKEN_COMMA));
				consume(Token::TokenType::TOKEN_RIGHT_PAREN,"Expect ')' after function args.");
			}
			return new FuncExpr(name.getLexeme(), args, name.getLine());
		}
		else
		{
			return new VarExpr(name.getLexeme(), name.getLine());
		}
	}
	error(&*m_Current, "Expect expression.");
	return nullptr;
}

Stmt *Parser::block()
{
	unsigned int line = previous().getLine();
	std::vector<Stmt *> statements;
	while (!check(Token::TokenType::TOKEN_RIGHT_BRACE) && !isAtEnd())
	{
		Stmt *stmt = declaration();
		if (stmt != nullptr)
		{
			statements.push_back(stmt);
		}
	}
	return new BlockStmt(statements, line);
}

Stmt *Parser::declaration()
{
	if (matchDatatype())
	{
		LixDatatype type = tokenToDatatype(previous().getType());
		Token name = consume(Token::TokenType::TOKEN_IDENTIFIER, "Expect name.");
		if (match(Token::TokenType::TOKEN_LEFT_PAREN))
		{
			return funDeclaration(type, name);
		}
		else
		{
			return varDeclaration(type, name);
		}
	}
	if (m_bPanicMode)
	{
		m_bPanicMode = false;
		synchronize();
		return nullptr;
	}
	return statement();
}

Stmt *Parser::varDeclaration(LixDatatype type, Token name)
{
	Expr *initializer = nullptr;
	if (match(Token::TokenType::TOKEN_EQUAL))
	{
		initializer = expression();
		/*
		if (initializer->resultingType() != type)
		{
			error(&*m_Current, "Type of variable: " + name.getLexeme() + " (" + lixDatatypeToString(type) + ") and initializer: (" + lixDatatypeToString(initializer->resultingType()) + ") does not match.");
		}
		*/
	}
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after variable declaration.");
	//addVar(Variable(type, name.getLexeme(), m_uiCurrentDepth));
	return new VarStmt(name.getLexeme(), type, initializer, name.getLine());
}

Stmt *Parser::funDeclaration(LixDatatype type, Token name)
{
	std::vector<std::pair<LixDatatype, std::string>> args;
	if (!check(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		do
		{
			if (matchDatatype())
			{
				LixDatatype type = tokenToDatatype(previous().getType());
				if (match(Token::TokenType::TOKEN_IDENTIFIER))
				{
					std::string name = previous().getLexeme();
					args.push_back(std::make_pair(type, name));
				}
			}
		} while (match(Token::TokenType::TOKEN_COMMA));
	}
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after function header.");
	consume(Token::TokenType::TOKEN_LEFT_BRACE, "Expect '{' after function header.");
	Stmt *body = block();
	consume(Token::TokenType::TOKEN_RIGHT_BRACE, "Expected closing '}' after function.");
	return new FuncDecl(name.getLexeme(), args, body, name.getLine());
}

Stmt *Parser::returnStmt()
{
	unsigned int line = previous().getLine();
	Expr *expr = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return new ReturnStmt(expr, line);
}

Stmt *Parser::statement()
{
	if (match(Token::TokenType::TOKEN_PRINT))
	{
		return printStatement();
	}
	if (match(Token::TokenType::TOKEN_LEFT_BRACE))
	{
		Stmt *result = block();
		consume(Token::TokenType::TOKEN_RIGHT_BRACE, "Expected closing '}'.");
		return result;
	}
	if (match(Token::TokenType::TOKEN_IF))
	{
		return ifStatement();
	}
	if (match(Token::TokenType::TOKEN_WHILE))
	{
		return whileStatement();
	}
	if (match(Token::TokenType::TOKEN_FOR))
	{
		return forStatement();
	}
	if (match(Token::TokenType::TOKEN_RETURN))
	{
		return returnStmt();
	}
	return expressionStatement();
}

Stmt *Parser::printStatement()
{
	unsigned int line = previous().getLine();
	Expr *value = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return new PrintStmt(value, line);
}

Stmt *Parser::ifStatement()
{
	unsigned int line = previous().getLine();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'if'.");
	Expr *condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	Stmt *then = statement();
	Stmt *elsestmt = nullptr;
	if (match(Token::TokenType::TOKEN_ELSE))
	{
		elsestmt = statement();
	}
	return new IfStmt(condition, then, elsestmt, line);
}

Stmt *Parser::whileStatement()
{
	unsigned int line = previous().getLine();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'while'.");
	Expr *condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	Stmt *body = statement();

	return new WhileStmt(condition, body, line);
}

Stmt *Parser::forStatement()
{
	unsigned int line = previous().getLine();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");
	Stmt *initializer = nullptr;
	if (match(Token::TokenType::TOKEN_SEMICOLON))
	{
	}
	else if (matchDatatype())
	{
		LixDatatype type = tokenToDatatype(previous().getType());
		Token name = consume(Token::TokenType::TOKEN_IDENTIFIER, "Expect name.");
		initializer = varDeclaration(type, name);
	}
	else
	{
		initializer = expressionStatement();
	}

	Expr *condition = nullptr;
	if (!check(Token::TokenType::TOKEN_SEMICOLON))
	{
		condition = expression();
	}
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after loop condition.");

	Expr *increment = nullptr;
	if (!check(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		increment = expression();
	}
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after for clauses.");

	Stmt *body = statement();
	return new BlockStmt({new ForStmt(condition, body, initializer, increment, line)}, line);
}

Stmt *Parser::expressionStatement()
{
	Expr *expr = expression();
	ExprStmt *exprstmt = new ExprStmt(expr, expr->getLine());
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return exprstmt;
}

void Parser::error(Token *p_pToken, const std::string &p_sMessage)
{
	m_bHadError = true;
	m_bPanicMode = true;
	m_Logger->log("Error at line: " + std::to_string(p_pToken->getLine()) + ". " + p_sMessage, Logger::Error);
}

void Parser::synchronize()
{
	while (m_Current->getType() != Token::TokenType::TOKEN_EOF)
	{
		if (previous().getType() == Token::TokenType::TOKEN_SEMICOLON)
		{
			return;
		}
		switch (m_Current->getType())
		{
		case Token::TokenType::TOKEN_CLASS:
		case Token::TokenType::TOKEN_FUN:
		case Token::TokenType::TOKEN_VAR:
		case Token::TokenType::TOKEN_FOR:
		case Token::TokenType::TOKEN_IF:
		case Token::TokenType::TOKEN_WHILE:
		case Token::TokenType::TOKEN_PRINT:
		case Token::TokenType::TOKEN_RETURN:
			return;
		default:
			break;
		}
		advance();
	}
}

std::vector<Stmt *> Parser::parse()
{
	Token token(Token::TokenType::TOKEN_EOF, 0);
	do
	{
		token = m_Scanner.scanToken();
		std::cout << token << " - " << token.getLine() << std::endl;
		if (token.getType() == Token::TokenType::TOKEN_ERROR)
		{
			error(&token, token.getLexeme());
		}
		else
		{
			m_Tokens.push_back(token);
		}

	} while (token.getType() != Token::TokenType::TOKEN_EOF);
	m_Current = m_Tokens.begin();
	std::vector<Stmt *> statements;
	while (!isAtEnd())
	{
		Stmt *stmt = declaration();
		if (stmt != nullptr)
		{
			statements.push_back(stmt);
		}
	}
	return statements;
}

bool Parser::hadError()
{
	return m_bHadError;
}