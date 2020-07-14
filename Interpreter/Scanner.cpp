#include "Scanner.hpp"
#include <iostream>
#include <iomanip>
#include <string>

Scanner::Scanner(std::string p_sSrc) : m_sSrc(p_sSrc), m_uiLine(1), m_uiCurrent(0), m_uiStart(0)
{
}

Scanner::~Scanner()
{
}

bool Scanner::isAtEnd()
{
    return m_uiCurrent >= m_sSrc.size();
}

char Scanner::advance()
{
    return m_sSrc[m_uiCurrent++];
}

Token Scanner::makeToken(Token::TokenType p_Type)
{
    if (p_Type == Token::TokenType::TOKEN_STRING)
    {
        return Token(p_Type, m_uiLine, m_sSrc.substr(m_uiStart + 1, m_uiCurrent - m_uiStart - 2));
    }
    return Token(p_Type, m_uiLine, m_sSrc.substr(m_uiStart, m_uiCurrent - m_uiStart));
}

bool Scanner::match(char p_cExpected)
{
    if (isAtEnd())
    {
        return false;
    }
    if (m_sSrc[m_uiCurrent] != p_cExpected)
    {
        return false;
    }
    m_uiCurrent++;
    return true;
}

char Scanner::peek()
{
    return m_sSrc[m_uiCurrent];
}

char Scanner::peekNext()
{
    if (isAtEnd())
    {
        return '\0';
    }
    return m_sSrc[m_uiCurrent + 1];
}

void Scanner::skipWhitespace()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            m_uiLine++;
            advance();
            break;
        case '/':
            if (peekNext() == '/')
            {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd())
                {
                    advance();
                }
            }
            else
            {
                return;
            }
            break;
        default:
            return;
        }
    }
}

Token Scanner::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
        {
            m_uiLine++;
        }
        advance();
    }

    if (isAtEnd())
    {
        return Token(Token::TokenType::TOKEN_ERROR, m_uiLine, "Unterminated string.");
    }

    // The closing ".
    advance();
    return makeToken(Token::TokenType::TOKEN_STRING);
}

bool Scanner::isDigit(char p_cCharacter)
{
    return p_cCharacter >= '0' && p_cCharacter <= '9';
}
Token Scanner::number()
{
    bool pointnumber = false;
    while (isDigit(peek()))
    {
        advance();
    }

    if (peek() == '.' && isDigit(peekNext()))
    {
        pointnumber = true;
        advance();

        while (isDigit(peek()))
        {
            advance();
        }
    }

    switch (peek())
    {
    case 'b':
        advance();
        return makeToken(Token::TokenType::TOKEN_NUMBER_BYTE);
        break;
    case 's':
        advance();
        return makeToken(Token::TokenType::TOKEN_NUMBER_SHORT);
        break;
    case 'i':
        advance();
        return makeToken(Token::TokenType::TOKEN_NUMBER_INT);
        break;
    case 'f':
        advance();
        return makeToken(Token::TokenType::TOKEN_NUMBER_FLOAT);
        break;
    case 'd':
        advance();
        return makeToken(Token::TokenType::TOKEN_NUMBER_DOUBLE);
        break;
    case 'l':
        advance();
        return makeToken(Token::TokenType::TOKEN_NUMBER_LONG);
        break;

    default:
        if (pointnumber)
        {
            return makeToken(Token::TokenType::TOKEN_NUMBER_FLOAT);
        }
        else
        {
            return makeToken(Token::TokenType::TOKEN_NUMBER_INT);
        }
        break;
    }
}

bool Scanner::isAlpha(char p_cCharacter)
{
    return (p_cCharacter >= 'a' && p_cCharacter <= 'z') ||
           (p_cCharacter >= 'A' && p_cCharacter <= 'Z') ||
           p_cCharacter == '_';
}
Token Scanner::identifier()
{
    while (isAlpha(peek()) || isDigit(peek()))
    {
        advance();
    }

    return makeToken(identifierType());
}

Token::TokenType Scanner::identifierType()
{
    switch (m_sSrc[m_uiStart])
    {
    case 'a':
        return checkKeyword(1, 2, "nd", Token::TokenType::TOKEN_AND);
    case 'b':
        if (m_uiCurrent - m_uiStart > 1)
        {
            switch (m_sSrc[m_uiStart + 1])
            {
            case 'o':
                return checkKeyword(2, 2, "ol", Token::TokenType::TOKEN_BOOL);
            case 'y':
                return checkKeyword(2, 2, "te", Token::TokenType::TOKEN_BYTE);
            case 'r':
                return checkKeyword(2, 3, "eak", Token::TokenType::TOKEN_BREAK);
            }
        }
        break;
    case 'c':
        if (m_uiCurrent - m_uiStart > 1)
        {
            switch (m_sSrc[m_uiStart + 1])
            {
            case 'l':
                return checkKeyword(1, 3, "ass", Token::TokenType::TOKEN_CLASS);
            case 'o':
                return checkKeyword(2, 6, "ntinue", Token::TokenType::TOKEN_CONTINUE);
            }
        }
        break;
    case 'd':
        return checkKeyword(1, 5, "ouble", Token::TokenType::TOKEN_DOUBLE);
    case 'e':
        return checkKeyword(1, 3, "lse", Token::TokenType::TOKEN_ELSE);
    case 'f':
        if (m_uiCurrent - m_uiStart > 1)
        {
            switch (m_sSrc[m_uiStart + 1])
            {
            case 'a':
                return checkKeyword(2, 3, "lse", Token::TokenType::TOKEN_FALSE);
            case 'o':
                return checkKeyword(2, 1, "r", Token::TokenType::TOKEN_FOR);
            case 'u':
                return checkKeyword(2, 1, "n", Token::TokenType::TOKEN_FUN);
            case 'l':
                return checkKeyword(2, 3, "oat", Token::TokenType::TOKEN_FLOAT);
            }
        }
        break;
    case 'i':
        if (m_uiCurrent - m_uiStart > 1)
        {
            switch (m_sSrc[m_uiStart + 1])
            {
            case 'f':
                return checkKeyword(2, 0, "", Token::TokenType::TOKEN_IF);
            case 'n':
                return checkKeyword(2, 1, "t", Token::TokenType::TOKEN_INT);
            }
        }
        break;
    case 'l':
        return checkKeyword(1, 3, "ong", Token::TokenType::TOKEN_LONG);
    case 'n':
        return checkKeyword(1, 2, "il", Token::TokenType::TOKEN_NIL);
    case 'o':
        return checkKeyword(1, 1, "r", Token::TokenType::TOKEN_OR);
    case 'p':
        return checkKeyword(1, 4, "rint", Token::TokenType::TOKEN_PRINT);
    case 'r':
        return checkKeyword(1, 5, "eturn", Token::TokenType::TOKEN_RETURN);
    case 's':
        if (m_uiCurrent - m_uiStart > 1)
        {
            switch (m_sSrc[m_uiStart + 1])
            {
            case 'h':
                return checkKeyword(2, 3, "ort", Token::TokenType::TOKEN_SHORT);
            case 'u':
                return checkKeyword(2, 3, "per", Token::TokenType::TOKEN_SUPER);
            }
        }
        break;
    case 't':
        if (m_uiCurrent - m_uiStart > 1)
        {
            switch (m_sSrc[m_uiStart + 1])
            {
            case 'h':
                return checkKeyword(2, 2, "is", Token::TokenType::TOKEN_THIS);
            case 'r':
                return checkKeyword(2, 2, "ue", Token::TokenType::TOKEN_TRUE);
            }
        }
        break;
    case 'v':
        return checkKeyword(1, 2, "ar", Token::TokenType::TOKEN_VAR);
    case 'w':
        return checkKeyword(1, 4, "hile", Token::TokenType::TOKEN_WHILE);
    }
    return Token::TokenType::TOKEN_IDENTIFIER;
}

Token::TokenType Scanner::checkKeyword(unsigned int p_uiStart, unsigned int p_uiLength, const std::string &p_sRest, Token::TokenType p_Type)
{
    if (p_uiStart + p_uiLength == m_uiCurrent - m_uiStart && p_sRest == m_sSrc.substr(m_uiStart + p_uiStart, m_uiCurrent - m_uiStart - p_uiStart))
    {
        return p_Type;
    }
    return Token::TokenType::TOKEN_IDENTIFIER;
}

Token Scanner::scanToken()
{
    skipWhitespace();
    if (isAtEnd())
    {
        return Token(Token::TokenType::TOKEN_EOF, m_uiLine);
    }
    m_uiStart = m_uiCurrent;
    char c = advance();
    if (isAlpha(c))
    {
        return identifier();
    }
    if (isDigit(c))
    {
        return number();
    }
    switch (c)
    {
    case '(':
        return makeToken(Token::TokenType::TOKEN_LEFT_PAREN);
    case ')':
        return makeToken(Token::TokenType::TOKEN_RIGHT_PAREN);
    case '{':
        return makeToken(Token::TokenType::TOKEN_LEFT_BRACE);
    case '}':
        return makeToken(Token::TokenType::TOKEN_RIGHT_BRACE);
    case ';':
        return makeToken(Token::TokenType::TOKEN_SEMICOLON);
    case ',':
        return makeToken(Token::TokenType::TOKEN_COMMA);
    case '.':
        return makeToken(Token::TokenType::TOKEN_DOT);
    case '-':
        return makeToken(Token::TokenType::TOKEN_MINUS);
    case '+':
        return makeToken(Token::TokenType::TOKEN_PLUS);
    case '/':
        return makeToken(Token::TokenType::TOKEN_SLASH);
    case '*':
        return makeToken(Token::TokenType::TOKEN_STAR);
    case '!':
        return makeToken(match('=') ? Token::TokenType::TOKEN_BANG_EQUAL : Token::TokenType::TOKEN_BANG);
    case '=':
        return makeToken(match('=') ? Token::TokenType::TOKEN_EQUAL_EQUAL : Token::TokenType::TOKEN_EQUAL);
    case '<':
        return makeToken(match('=') ? Token::TokenType::TOKEN_LESS_EQUAL : Token::TokenType::TOKEN_LESS);
    case '>':
        return makeToken(match('=') ? Token::TokenType::TOKEN_GREATER_EQUAL : Token::TokenType::TOKEN_GREATER);
    case '"':
        return string();
    //case '\'':

    }
    return Token(Token::TokenType::TOKEN_ERROR, m_uiLine, "Unexpected character: \"" + std::string(1, c) + "\".");
}