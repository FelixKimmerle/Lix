#pragma once
#include <string>
#include <vector>
#include "Token.hpp"
class Scanner
{
private:
    bool isAtEnd();
    char advance();
    bool match(char p_cExpected);
    void skipWhitespace();
    char peek();
    char peekNext();
    Token string();
    bool isDigit(char p_cCharacter);
    Token number();
    bool isAlpha(char p_cCharacter);
    Token identifier();
    Token::TokenType identifierType();
    Token makeToken(Token::TokenType p_Type);
    Token::TokenType checkKeyword(unsigned int p_uiStart, unsigned int p_uiLength, const std::string &p_sRest, Token::TokenType p_Type);

    const std::string m_sSrc;
    unsigned int m_uiLine;
    unsigned int m_uiCurrent;
    unsigned int m_uiStart;

public:
    Scanner(std::string p_sSrc);
    ~Scanner();
    Token scanToken();
};
