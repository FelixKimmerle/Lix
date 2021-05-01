#include "Token.hpp"
#include <ostream>
#include <iomanip>
std::ostream &operator<<(std::ostream &out, const Token &value)
{
    out << std::setfill(' ') << std::setw(2) << (int)value.token_type << " \'" << value.lexeme << "\'";
    return out;
}

Token::Token(TokenType token_type, TokenPosition position, std::string lexeme) : lexeme(lexeme), position(position), token_type(token_type)
{
}

Token::Token() : token_type(TokenType::TOKEN_ERROR)
{
}

Token::TokenType Token::get_type()const
{
    return token_type;
}

TokenPosition Token::get_position()const
{
    return position;
}

std::string Token::get_lexeme()const
{
    return lexeme;
}