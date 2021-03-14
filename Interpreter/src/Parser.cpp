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
#include "Expr/CallExpr.hpp"

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

std::unique_ptr<Expr> Parser::expression()
{
	std::unique_ptr<Expr> expr = logicalor();

	return expr;
}

std::unique_ptr<Expr> Parser::logicalor()
{
	std::unique_ptr<Expr> expr = logicaland();

	while (match(Token::TokenType::TOKEN_OR))
	{
		std::unique_ptr<Expr> right = logicaland();

		expr = std::make_unique<OrExpr>(std::move(expr), std::move(right), previous().getLine());
	}
	return expr;
}
std::unique_ptr<Expr> Parser::logicaland()
{
	std::unique_ptr<Expr> expr = equality();

	while (match(Token::TokenType::TOKEN_AND))
	{
		std::unique_ptr<Expr> right = equality();

		expr = std::make_unique<AndExpr>(std::move(expr), std::move(right), previous().getLine());
	}
	return expr;
}
std::unique_ptr<Expr> Parser::equality()
{
	std::unique_ptr<Expr> expr = comparison();

	while (match({Token::TokenType::TOKEN_BANG_EQUAL, Token::TokenType::TOKEN_EQUAL_EQUAL}))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = comparison();

		if (op.getType() == Token::TokenType::TOKEN_EQUAL_EQUAL)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_EQUAL, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_BANG_EQUAL)
		{
			expr = std::make_unique<UnaryExpr>(std::make_unique<ComparisonExpr>(std::move(expr), std::move(right),
																				ComparisonExpr::ComparisonOperator::BO_EQUAL, op.getLine()),
											   UnaryExpr::UnaryOperator::UO_BANG, op.getLine());
		}
	}
	return expr;
}
std::unique_ptr<Expr> Parser::comparison()
{
	std::unique_ptr<Expr> expr = addition();

	while (match({Token::TokenType::TOKEN_GREATER,
				  Token::TokenType::TOKEN_GREATER_EQUAL,
				  Token::TokenType::TOKEN_LESS,
				  Token::TokenType::TOKEN_LESS_EQUAL}))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = addition();

		if (op.getType() == Token::TokenType::TOKEN_GREATER)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_GREATER, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_LESS)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_LESS, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_GREATER_EQUAL)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_GREATER_EQUAL, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_LESS_EQUAL)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_LESS_EQUAL, op.getLine());
		}
	}
	return expr;
}

std::unique_ptr<Expr> Parser::addition()
{
	std::unique_ptr<Expr> expr = multiplication();

	while (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_PLUS}))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = addition();

		if (op.getType() == Token::TokenType::TOKEN_MINUS)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_SUB, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_PLUS)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_ADD, op.getLine());
		}
	}

	return expr;
}
std::unique_ptr<Expr> Parser::multiplication()
{
	std::unique_ptr<Expr> expr = unary();

	while (match({Token::TokenType::TOKEN_SLASH, Token::TokenType::TOKEN_STAR}))
	{
		Token op = previous();
		std::unique_ptr<Expr> right = unary();

		if (op.getType() == Token::TokenType::TOKEN_SLASH)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_DIV, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_STAR)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_MUL, op.getLine());
		}
	}

	return expr;
}
std::unique_ptr<Expr> Parser::unary()
{
	if (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_BANG}) || matchDatatype())
	{
		Token op = previous();
		if (op.getType() == Token::TokenType::TOKEN_MINUS)
		{
			return std::make_unique<UnaryExpr>(std::move(unary()), UnaryExpr::UO_MINUS, op.getLine());
		}
		else if (op.getType() == Token::TokenType::TOKEN_BANG)
		{
			return std::make_unique<UnaryExpr>(std::move(unary()), UnaryExpr::UO_BANG, op.getLine());
		}
		else
		{
			consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' between cast and expression.");
			std::unique_ptr<Expr> right = unary();
			consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after cast.");
			return std::make_unique<ExplicitCastExpr>(std::move(right), tokenToDatatype(op.getType()), op.getLine());
		}
	}

	return call();
}

std::unique_ptr<Expr> Parser::finishCall(std::unique_ptr<Expr> callee)
{
	std::vector<std::unique_ptr<Expr>> args;

	std::unique_ptr<CallExpr> call_expr = std::make_unique<CallExpr>(std::move(callee), previous().getLine());

	if (!match(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		do
		{
			call_expr->add_param(std::move(expression()));
		} while (match(Token::TokenType::TOKEN_COMMA));
		consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after function args.");
	}
	return call_expr;
}

std::unique_ptr<Expr> Parser::call()
{
	std::unique_ptr<Expr> expr = literal();

	while (true)
	{
		if (match(Token::TokenType::TOKEN_LEFT_PAREN))
		{
			expr = finishCall(std::move(expr));
		}
		else
		{
			break;
		}
	}

	return expr;
}

std::unique_ptr<Expr> Parser::literal()
{
	if (match(Token::TokenType::TOKEN_FALSE))
	{
		return std::make_unique<BooleanExpr>(false, previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_TRUE))
	{
		return std::make_unique<BooleanExpr>(true, previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_BYTE))
	{
		return std::make_unique<NumberExpr<Lix_Byte>>(static_cast<Lix_Byte>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_SHORT))
	{
		return std::make_unique<NumberExpr<Lix_ShortInt>>(static_cast<Lix_ShortInt>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_INT))
	{
		return std::make_unique<NumberExpr<Lix_Int>>(static_cast<Lix_Int>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_FLOAT))
	{
		return std::make_unique<NumberExpr<Lix_Float>>(static_cast<Lix_Float>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_DOUBLE))
	{
		return std::make_unique<NumberExpr<Lix_Double>>(static_cast<Lix_Double>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_LONG))
	{
		return std::make_unique<NumberExpr<Lix_LongInt>>(static_cast<Lix_LongInt>(std::stol(previous().getLexeme())), previous().getLine());
	}
	if (match(Token::TokenType::TOKEN_LEFT_PAREN))
	{
		std::unique_ptr<Expr> expr = expression();
		consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
		return std::make_unique<GroupingExpr>(std::move(expr), expr->getLine());
	}
	if (match(Token::TokenType::TOKEN_IDENTIFIER))
	{
		Token name = previous();
		if (match(Token::TokenType::TOKEN_EQUAL))
		{
			std::unique_ptr<VarExpr> var = std::make_unique<VarExpr>(name.getLexeme(), name.getLine());
			std::unique_ptr<Expr> assignexpr = expression();
			/*
			if (assignexpr->resultingType() != var->resultingType())
			{
				error(&name, "Type of variable: " + name.getLexeme() + " (" + lixDatatypeToString(var->resultingType()) + ") and assignment: (" + lixDatatypeToString(assignexpr->resultingType()) + ") does not match.");
			}
			*/
			return std::make_unique<AssignExpr>(std::move(var), std::move(assignexpr), name.getLine());
		}
		else
		{
			return std::make_unique<VarExpr>(name.getLexeme(), name.getLine());
		}
	}
	error(&*m_Current, "Expect expression.");
	return nullptr;
}

std::unique_ptr<BlockStmt> Parser::block()
{
	unsigned int line = previous().getLine();
	std::unique_ptr<BlockStmt> block_stmt = std::make_unique<BlockStmt>(line);
	while (!check(Token::TokenType::TOKEN_RIGHT_BRACE) && !isAtEnd())
	{
		std::unique_ptr<Stmt> stmt = declaration();
		if (stmt != nullptr)
		{
			block_stmt->add(std::move(stmt));
		}
	}
	return block_stmt;
}

std::unique_ptr<Stmt> Parser::declaration()
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

std::unique_ptr<Stmt> Parser::varDeclaration(LixDatatype type, Token name)
{
	std::unique_ptr<Expr> initializer = nullptr;
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
	return std::make_unique<VarStmt>(name.getLexeme(), type, std::move(initializer), name.getLine());
}

std::unique_ptr<Stmt> Parser::funDeclaration(LixDatatype type, Token name)
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
	std::unique_ptr<BlockStmt> body = block();
	consume(Token::TokenType::TOKEN_RIGHT_BRACE, "Expected closing '}' after function.");
	return std::make_unique<FuncDecl>(name.getLexeme(), type, args, std::move(body), name.getLine());
}

std::unique_ptr<Stmt> Parser::returnStmt()
{
	unsigned int line = previous().getLine();
	std::unique_ptr<Expr> expr = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return std::make_unique<ReturnStmt>(std::move(expr), line);
}

std::unique_ptr<Stmt> Parser::statement()
{
	if (match(Token::TokenType::TOKEN_PRINT))
	{
		return printStatement();
	}
	if (match(Token::TokenType::TOKEN_LEFT_BRACE))
	{
		std::unique_ptr<Stmt> result = block();
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

std::unique_ptr<Stmt> Parser::printStatement()
{
	unsigned int line = previous().getLine();
	std::unique_ptr<Expr> value = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return std::make_unique<PrintStmt>(std::move(value), line);
}

std::unique_ptr<Stmt> Parser::ifStatement()
{
	unsigned int line = previous().getLine();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'if'.");
	std::unique_ptr<Expr> condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	std::unique_ptr<Stmt> then = statement();
	std::unique_ptr<Stmt> elsestmt = nullptr;
	if (match(Token::TokenType::TOKEN_ELSE))
	{
		elsestmt = statement();
	}
	return std::make_unique<IfStmt>(std::move(condition), std::move(then), std::move(elsestmt), line);
}

std::unique_ptr<Stmt> Parser::whileStatement()
{
	unsigned int line = previous().getLine();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'while'.");
	std::unique_ptr<Expr> condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	std::unique_ptr<Stmt> body = statement();

	return std::make_unique<WhileStmt>(std::move(condition), std::move(body), line);
}

std::unique_ptr<Stmt> Parser::forStatement()
{
	unsigned int line = previous().getLine();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");
	std::unique_ptr<Stmt> initializer = nullptr;
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

	std::unique_ptr<Expr> condition = nullptr;
	if (!check(Token::TokenType::TOKEN_SEMICOLON))
	{
		condition = expression();
	}
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after loop condition.");

	std::unique_ptr<Expr> increment = nullptr;
	if (!check(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		increment = expression();
	}
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after for clauses.");

	std::unique_ptr<Stmt> body = statement();

	std::unique_ptr<BlockStmt> block_stmt = std::make_unique<BlockStmt>(line);
	block_stmt->add(std::move(std::make_unique<ForStmt>(std::move(condition), std::move(body), std::move(initializer), std::move(increment), line)));
	return block_stmt;
}

std::unique_ptr<Stmt> Parser::expressionStatement()
{
	std::unique_ptr<Expr> expr = expression();
	std::unique_ptr<ExprStmt> exprstmt = std::make_unique<ExprStmt>(std::move(expr), expr->getLine());
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

std::unique_ptr<BlockStmt> Parser::parse()
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

	std::unique_ptr<BlockStmt> statements = std::make_unique<BlockStmt>(0);
	while (!isAtEnd())
	{
		std::unique_ptr<Stmt> stmt = declaration();
		if (stmt != nullptr)
		{
			statements->add(std::move(stmt));
		}
	}
	return statements;
}

bool Parser::hadError()
{
	return m_bHadError;
}