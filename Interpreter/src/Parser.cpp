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
#include <sstream>

Parser::Parser(std::string source, Logger *logger) : scanner("test.lix",source), had_error(false), logger(logger), panic_mode(false)
{
}

bool Parser::match(const std::vector<Token::TokenType> &types)
{
	for (auto &&type : types)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}
	return false;
}
bool Parser::match(const Token::TokenType &type)
{
	if (check(type))
	{
		advance();
		return true;
	}
	return false;
}
bool Parser::check(const Token::TokenType &token_type)
{
	if (is_at_end())
	{
		return false;
	}
	return current.get_type() == token_type;
}
bool Parser::check_next(const Token::TokenType &token_type)
{
	if (is_at_end())
	{
		return false;
	}
	if (last.get_type() == Token::TokenType::TOKEN_EOF)
	{
		return false;
	}
	return last.get_type() == token_type;
}
bool Parser::is_at_end()
{
	return current.get_type() == Token::TokenType::TOKEN_EOF;
}

Token Parser::advance()
{
	if (!is_at_end())
	{
		last = current;
		current = scanner.scanToken();
	}
	return last;
}
Token Parser::consume(Token::TokenType token_type, const std::string &message)
{
	if (check(token_type))
	{
		return advance();
	}
	error(current, message);
	return current;
}

LixDatatype Parser::token_to_datatype(Token::TokenType token_type)
{
	switch (token_type)
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

bool Parser::match_datatype()
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

		expr = std::make_unique<OrExpr>(std::move(expr), std::move(right), last.get_position());
	}
	return expr;
}
std::unique_ptr<Expr> Parser::logicaland()
{
	std::unique_ptr<Expr> expr = equality();

	while (match(Token::TokenType::TOKEN_AND))
	{
		std::unique_ptr<Expr> right = equality();

		expr = std::make_unique<AndExpr>(std::move(expr), std::move(right), last.get_position());
	}
	return expr;
}
std::unique_ptr<Expr> Parser::equality()
{
	std::unique_ptr<Expr> expr = comparison();

	while (match({Token::TokenType::TOKEN_BANG_EQUAL, Token::TokenType::TOKEN_EQUAL_EQUAL}))
	{
		Token op = last;
		std::unique_ptr<Expr> right = comparison();

		if (op.get_type() == Token::TokenType::TOKEN_EQUAL_EQUAL)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_EQUAL, op.get_position());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_BANG_EQUAL)
		{
			expr = std::make_unique<UnaryExpr>(std::make_unique<ComparisonExpr>(std::move(expr), std::move(right),
																				ComparisonExpr::ComparisonOperator::BO_EQUAL, op.get_position()),
											   UnaryExpr::UnaryOperator::UO_BANG, op.get_position());
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
		Token op = last;
		std::unique_ptr<Expr> right = addition();

		if (op.get_type() == Token::TokenType::TOKEN_GREATER)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_GREATER, op.get_position());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_LESS)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_LESS, op.get_position());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_GREATER_EQUAL)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_GREATER_EQUAL, op.get_position());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_LESS_EQUAL)
		{
			expr = std::make_unique<ComparisonExpr>(std::move(expr), std::move(right), ComparisonExpr::ComparisonOperator::BO_LESS_EQUAL, op.get_position());
		}
	}
	return expr;
}

std::unique_ptr<Expr> Parser::addition()
{
	std::unique_ptr<Expr> expr = multiplication();

	while (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_PLUS}))
	{
		Token op = last;
		std::unique_ptr<Expr> right = addition();

		if (op.get_type() == Token::TokenType::TOKEN_MINUS)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_SUB, op.get_position());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_PLUS)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_ADD, op.get_position());
		}
	}

	return expr;
}
std::unique_ptr<Expr> Parser::multiplication()
{
	std::unique_ptr<Expr> expr = unary();

	while (match({Token::TokenType::TOKEN_SLASH, Token::TokenType::TOKEN_STAR}))
	{
		Token op = last;
		std::unique_ptr<Expr> right = unary();

		if (op.get_type() == Token::TokenType::TOKEN_SLASH)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_DIV, op.get_position());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_STAR)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BO_MUL, op.get_position());
		}
	}

	return expr;
}
std::unique_ptr<Expr> Parser::unary()
{
	if (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_BANG}) || match_datatype())
	{
		Token op = last;
		if (op.get_type() == Token::TokenType::TOKEN_MINUS)
		{
			return std::make_unique<UnaryExpr>(std::move(unary()), UnaryExpr::UO_MINUS, op.get_position());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_BANG)
		{
			return std::make_unique<UnaryExpr>(std::move(unary()), UnaryExpr::UO_BANG, op.get_position());
		}
		else
		{
			consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' between cast and expression.");
			std::unique_ptr<Expr> right = unary();
			consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after cast.");
			return std::make_unique<ExplicitCastExpr>(std::move(right), token_to_datatype(op.get_type()), op.get_position());
		}
	}

	return call();
}

std::unique_ptr<Expr> Parser::finish_call(std::unique_ptr<Expr> callee)
{
	std::vector<std::unique_ptr<Expr>> args;

	std::unique_ptr<CallExpr> call_expr = std::make_unique<CallExpr>(std::move(callee), last.get_position());

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
			expr = finish_call(std::move(expr));
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
		return std::make_unique<BooleanExpr>(false, last.get_position());
	}
	if (match(Token::TokenType::TOKEN_TRUE))
	{
		return std::make_unique<BooleanExpr>(true, last.get_position());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_BYTE))
	{
		return std::make_unique<NumberExpr<Lix_Byte>>(static_cast<Lix_Byte>(std::stol(last.get_lexeme())), last.get_position());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_SHORT))
	{
		return std::make_unique<NumberExpr<Lix_ShortInt>>(static_cast<Lix_ShortInt>(std::stol(last.get_lexeme())), last.get_position());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_INT))
	{
		return std::make_unique<NumberExpr<Lix_Int>>(static_cast<Lix_Int>(std::stol(last.get_lexeme())), last.get_position());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_FLOAT))
	{
		return std::make_unique<NumberExpr<Lix_Float>>(static_cast<Lix_Float>(std::stol(last.get_lexeme())), last.get_position());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_DOUBLE))
	{
		return std::make_unique<NumberExpr<Lix_Double>>(static_cast<Lix_Double>(std::stol(last.get_lexeme())), last.get_position());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_LONG))
	{
		return std::make_unique<NumberExpr<Lix_LongInt>>(static_cast<Lix_LongInt>(std::stol(last.get_lexeme())), last.get_position());
	}
	if (match(Token::TokenType::TOKEN_LEFT_PAREN))
	{
		std::unique_ptr<Expr> expr = expression();
		consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
		return std::make_unique<GroupingExpr>(std::move(expr), expr->get_position());
	}
	if (match(Token::TokenType::TOKEN_IDENTIFIER))
	{
		Token name = last;
		if (match(Token::TokenType::TOKEN_EQUAL))
		{
			std::unique_ptr<VarExpr> var = std::make_unique<VarExpr>(name.get_lexeme(), name.get_position());
			std::unique_ptr<Expr> assignexpr = expression();
			/*
			if (assignexpr->resultingType() != var->resultingType())
			{
				error(&name, "Type of variable: " + name.getLexeme() + " (" + lixDatatypeToString(var->resultingType()) + ") and assignment: (" + lixDatatypeToString(assignexpr->resultingType()) + ") does not match.");
			}
			*/
			return std::make_unique<AssignExpr>(std::move(var), std::move(assignexpr), name.get_position());
		}
		else
		{
			return std::make_unique<VarExpr>(name.get_lexeme(), name.get_position());
		}
	}
	error(current, "Expect expression.");
	return nullptr;
}

std::unique_ptr<BlockStmt> Parser::block()
{
	std::unique_ptr<BlockStmt> block_stmt = std::make_unique<BlockStmt>(last.get_position());
	while (!check(Token::TokenType::TOKEN_RIGHT_BRACE) && !is_at_end())
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
	if (match_datatype())
	{
		LixDatatype type = token_to_datatype(last.get_type());
		Token name = consume(Token::TokenType::TOKEN_IDENTIFIER, "Expect name.");
		if (match(Token::TokenType::TOKEN_LEFT_PAREN))
		{
			return fun_declaration(type, name);
		}
		else
		{
			return var_declaration(type, name);
		}
	}
	if (panic_mode)
	{
		panic_mode = false;
		synchronize();
		return nullptr;
	}
	return statement();
}

std::unique_ptr<Stmt> Parser::var_declaration(LixDatatype type, Token name)
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
	return std::make_unique<VarStmt>(name.get_lexeme(), type, std::move(initializer), name.get_position());
}

std::unique_ptr<Stmt> Parser::fun_declaration(LixDatatype type, Token name)
{
	std::vector<std::pair<LixDatatype, std::string>> args;
	if (!check(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		do
		{
			if (match_datatype())
			{
				LixDatatype type = token_to_datatype(last.get_type());
				if (match(Token::TokenType::TOKEN_IDENTIFIER))
				{
					std::string name = last.get_lexeme();
					args.push_back(std::make_pair(type, name));
				}
			}
		} while (match(Token::TokenType::TOKEN_COMMA));
	}
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after function header.");
	consume(Token::TokenType::TOKEN_LEFT_BRACE, "Expect '{' after function header.");
	std::unique_ptr<BlockStmt> body = block();
	consume(Token::TokenType::TOKEN_RIGHT_BRACE, "Expected closing '}' after function.");
	return std::make_unique<FuncDecl>(name.get_lexeme(), type, args, std::move(body), name.get_position());
}

std::unique_ptr<Stmt> Parser::return_stmt()
{
	TokenPosition position = last.get_position();
	std::unique_ptr<Expr> expr = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return std::make_unique<ReturnStmt>(std::move(expr), position);
}

std::unique_ptr<Stmt> Parser::statement()
{
	if (match(Token::TokenType::TOKEN_PRINT))
	{
		return print_statement();
	}
	if (match(Token::TokenType::TOKEN_LEFT_BRACE))
	{
		std::unique_ptr<Stmt> result = block();
		consume(Token::TokenType::TOKEN_RIGHT_BRACE, "Expected closing '}'.");
		return result;
	}
	if (match(Token::TokenType::TOKEN_IF))
	{
		return if_statement();
	}
	if (match(Token::TokenType::TOKEN_WHILE))
	{
		return while_statement();
	}
	if (match(Token::TokenType::TOKEN_FOR))
	{
		return for_statement();
	}
	if (match(Token::TokenType::TOKEN_RETURN))
	{
		return return_stmt();
	}
	return expression_statement();
}

std::unique_ptr<Stmt> Parser::print_statement()
{
	TokenPosition position = last.get_position();
	std::unique_ptr<Expr> value = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return std::make_unique<PrintStmt>(std::move(value), position);
}

std::unique_ptr<Stmt> Parser::if_statement()
{
	TokenPosition position = last.get_position();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'if'.");
	std::unique_ptr<Expr> condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	std::unique_ptr<Stmt> then = statement();
	std::unique_ptr<Stmt> elsestmt = nullptr;
	if (match(Token::TokenType::TOKEN_ELSE))
	{
		elsestmt = statement();
	}
	return std::make_unique<IfStmt>(std::move(condition), std::move(then), std::move(elsestmt), position);
}

std::unique_ptr<Stmt> Parser::while_statement()
{
	TokenPosition position = last.get_position();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'while'.");
	std::unique_ptr<Expr> condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	std::unique_ptr<Stmt> body = statement();

	return std::make_unique<WhileStmt>(std::move(condition), std::move(body), position);
}

std::unique_ptr<Stmt> Parser::for_statement()
{
	TokenPosition position = last.get_position();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");
	std::unique_ptr<Stmt> initializer = nullptr;
	if (match(Token::TokenType::TOKEN_SEMICOLON))
	{
	}
	else if (match_datatype())
	{
		LixDatatype type = token_to_datatype(last.get_type());
		Token name = consume(Token::TokenType::TOKEN_IDENTIFIER, "Expect name.");
		initializer = var_declaration(type, name);
	}
	else
	{
		initializer = expression_statement();
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

	std::unique_ptr<BlockStmt> block_stmt = std::make_unique<BlockStmt>(position);
	block_stmt->add(std::move(std::make_unique<ForStmt>(std::move(condition), std::move(body), std::move(initializer), std::move(increment), position)));
	return block_stmt;
}

std::unique_ptr<Stmt> Parser::expression_statement()
{
	std::unique_ptr<Expr> expr = expression();
	std::unique_ptr<ExprStmt> exprstmt = std::make_unique<ExprStmt>(std::move(expr), expr->get_position());
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return exprstmt;
}

void Parser::error(const Token &token, const std::string &message)
{
	had_error = true;
	panic_mode = true;

	std::stringstream ss;
	ss << token.get_position();


	logger->log("Error at line: " + ss.str() + ". " + message, Logger::Error);
}

void Parser::synchronize()
{
	while (current.get_type() != Token::TokenType::TOKEN_EOF)
	{
		if (last.get_type() == Token::TokenType::TOKEN_SEMICOLON)
		{
			return;
		}
		switch (current.get_type())
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
	advance();
	std::unique_ptr<BlockStmt> statements = std::make_unique<BlockStmt>(TokenPosition());
	while (!is_at_end())
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
	return had_error;
}