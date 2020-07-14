#include "Token.hpp"
#include <ostream>
#include <iomanip>
std::ostream &operator<<(std::ostream &out, const Token &value)
{
    out << std::setfill(' ') << std::setw(2) << (int)value.m_TokenType << " \'" << value.m_sLexeme << "\'";
    return out;
}

Token::Token(TokenType p_TokenType, unsigned int p_uiLine, std::string p_sLexeme) : m_sLexeme(p_sLexeme), m_uiLine(p_uiLine), m_TokenType(p_TokenType)
{
}

Token::Token() : m_TokenType(TokenType::TOKEN_ERROR)
{
}

Token::~Token()
{
}

Token::TokenType Token::getType()
{
    return m_TokenType;
}

unsigned int Token::getLine()
{
    return m_uiLine;
}

std::string Token::getLexeme()
{
    return m_sLexeme;
}