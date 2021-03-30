#include "Scanner.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

Scanner::Scanner(const std::string &file_name, const std::string &src) : src(src), file_name(file_name), line(1), column(0), current(0), start(0)
{
}

Scanner::Scanner(const std::string &file_name) : file_name(file_name), line(1), column(0), current(0), start(0)
{
    std::ifstream file_stream(file_name);

    file_stream.seekg(0, std::ios::end);
    src.reserve(file_stream.tellg());
    file_stream.seekg(0, std::ios::beg);

    src.assign((std::istreambuf_iterator<char>(file_stream)),
               std::istreambuf_iterator<char>());
}

bool Scanner::is_at_end()
{
    return current >= src.size();
}

char Scanner::advance()
{
    column++;
    return src[current++];
}

Token Scanner::make_token(Token::TokenType type)
{
    TokenPosition position(file_name, line, column);
    if (type == Token::TokenType::TOKEN_STRING)
    {
        return Token(type, position, src.substr(start + 1, current - start - 2));
    }
    return Token(type, position, src.substr(start, current - start));
}

bool Scanner::match(char expected)
{
    if (is_at_end())
    {
        return false;
    }
    if (src[current] != expected)
    {
        return false;
    }
    current++;
    column++;
    return true;
}

char Scanner::peek()
{
    return src[current];
}

char Scanner::peek_next()
{
    if (is_at_end())
    {
        return '\0';
    }
    return src[current + 1];
}

void Scanner::skip_whitespace()
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
            line++;
            column = 0;
            advance();
            break;
        case '/':
            if (peek_next() == '/')
            {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !is_at_end())
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
    while (peek() != '"' && !is_at_end())
    {
        if (peek() == '\n')
        {
            line++;
        }
        advance();
    }

    if (is_at_end())
    {
        return Token(Token::TokenType::TOKEN_ERROR, TokenPosition(file_name, line, column), "Unterminated string.");
    }

    // The closing ".
    advance();
    return make_token(Token::TokenType::TOKEN_STRING);
}

bool Scanner::is_digit(char character)
{
    return character >= '0' && character <= '9';
}
Token Scanner::number()
{
    bool decimal = false;
    while (is_digit(peek()))
    {
        advance();
    }

    if (peek() == '.' && is_digit(peek_next()))
    {
        decimal = true;
        advance();

        while (is_digit(peek()))
        {
            advance();
        }
    }

    switch (peek())
    {
    case 'b':
        advance();
        return make_token(Token::TokenType::TOKEN_NUMBER_BYTE);
        break;
    case 's':
        advance();
        return make_token(Token::TokenType::TOKEN_NUMBER_SHORT);
        break;
    case 'i':
        advance();
        return make_token(Token::TokenType::TOKEN_NUMBER_INT);
        break;
    case 'f':
        advance();
        return make_token(Token::TokenType::TOKEN_NUMBER_FLOAT);
        break;
    case 'd':
        advance();
        return make_token(Token::TokenType::TOKEN_NUMBER_DOUBLE);
        break;
    case 'l':
        advance();
        return make_token(Token::TokenType::TOKEN_NUMBER_LONG);
        break;

    default:
        if (decimal)
        {
            return make_token(Token::TokenType::TOKEN_NUMBER_FLOAT);
        }
        else
        {
            return make_token(Token::TokenType::TOKEN_NUMBER_INT);
        }
        break;
    }
}

bool Scanner::is_alpha(char character)
{
    return (character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z') ||
           character == '_';
}
Token Scanner::identifier()
{
    while (is_alpha(peek()) || is_digit(peek()))
    {
        advance();
    }

    return make_token(identifier_type());
}

Token::TokenType Scanner::identifier_type()
{
    switch (src[start])
    {
    case 'a':
        return check_keyword(1, 2, "nd", Token::TokenType::TOKEN_AND);
    case 'b':
        if (current - start > 1)
        {
            switch (src[start + 1])
            {
            case 'o':
                return check_keyword(2, 2, "ol", Token::TokenType::TOKEN_BOOL);
            case 'y':
                return check_keyword(2, 2, "te", Token::TokenType::TOKEN_BYTE);
            case 'r':
                return check_keyword(2, 3, "eak", Token::TokenType::TOKEN_BREAK);
            }
        }
        break;
    case 'c':
        if (current - start > 1)
        {
            switch (src[start + 1])
            {
            case 'l':
                return check_keyword(1, 3, "ass", Token::TokenType::TOKEN_CLASS);
            case 'o':
                return check_keyword(2, 6, "ntinue", Token::TokenType::TOKEN_CONTINUE);
            }
        }
        break;
    case 'd':
        return check_keyword(1, 5, "ouble", Token::TokenType::TOKEN_DOUBLE);
    case 'e':
        return check_keyword(1, 3, "lse", Token::TokenType::TOKEN_ELSE);
    case 'f':
        if (current - start > 1)
        {
            switch (src[start + 1])
            {
            case 'a':
                return check_keyword(2, 3, "lse", Token::TokenType::TOKEN_FALSE);
            case 'o':
                return check_keyword(2, 1, "r", Token::TokenType::TOKEN_FOR);
            case 'u':
                return check_keyword(2, 1, "n", Token::TokenType::TOKEN_FUN);
            case 'l':
                return check_keyword(2, 3, "oat", Token::TokenType::TOKEN_FLOAT);
            }
        }
        break;
    case 'i':
        if (current - start > 1)
        {
            switch (src[start + 1])
            {
            case 'f':
                return check_keyword(2, 0, "", Token::TokenType::TOKEN_IF);
            case 'n':
                return check_keyword(2, 1, "t", Token::TokenType::TOKEN_INT);
            }
        }
        break;
    case 'l':
        return check_keyword(1, 3, "ong", Token::TokenType::TOKEN_LONG);
    case 'n':
        return check_keyword(1, 2, "il", Token::TokenType::TOKEN_NIL);
    case 'o':
        return check_keyword(1, 1, "r", Token::TokenType::TOKEN_OR);
    case 'p':
        return check_keyword(1, 4, "rint", Token::TokenType::TOKEN_PRINT);
    case 'r':
        return check_keyword(1, 5, "eturn", Token::TokenType::TOKEN_RETURN);
    case 's':
        if (current - start > 1)
        {
            switch (src[start + 1])
            {
            case 'h':
                return check_keyword(2, 3, "ort", Token::TokenType::TOKEN_SHORT);
            case 'u':
                return check_keyword(2, 3, "per", Token::TokenType::TOKEN_SUPER);
            }
        }
        break;
    case 't':
        if (current - start > 1)
        {
            switch (src[start + 1])
            {
            case 'h':
                return check_keyword(2, 2, "is", Token::TokenType::TOKEN_THIS);
            case 'r':
                return check_keyword(2, 2, "ue", Token::TokenType::TOKEN_TRUE);
            }
        }
        break;
    case 'v':
        return check_keyword(1, 2, "ar", Token::TokenType::TOKEN_VAR);
    case 'w':
        return check_keyword(1, 4, "hile", Token::TokenType::TOKEN_WHILE);
    }
    return Token::TokenType::TOKEN_IDENTIFIER;
}

Token::TokenType Scanner::check_keyword(unsigned int start, unsigned int length, const std::string &rest, Token::TokenType type)
{
    if (start + length == current - start && rest == src.substr(start + start, current - start - start))
    {
        return type;
    }
    return Token::TokenType::TOKEN_IDENTIFIER;
}

Token Scanner::scanToken()
{
    skip_whitespace();
    if (is_at_end())
    {
        return Token(Token::TokenType::TOKEN_EOF, TokenPosition(file_name, line, column));
    }
    start = current;
    char c = advance();
    if (is_alpha(c))
    {
        return identifier();
    }
    if (is_digit(c))
    {
        return number();
    }
    switch (c)
    {
    case '(':
        return make_token(Token::TokenType::TOKEN_LEFT_PAREN);
    case ')':
        return make_token(Token::TokenType::TOKEN_RIGHT_PAREN);
    case '{':
        return make_token(Token::TokenType::TOKEN_LEFT_BRACE);
    case '}':
        return make_token(Token::TokenType::TOKEN_RIGHT_BRACE);
    case ';':
        return make_token(Token::TokenType::TOKEN_SEMICOLON);
    case ',':
        return make_token(Token::TokenType::TOKEN_COMMA);
    case '.':
        return make_token(Token::TokenType::TOKEN_DOT);
    case '-':
        return make_token(Token::TokenType::TOKEN_MINUS);
    case '+':
        return make_token(Token::TokenType::TOKEN_PLUS);
    case '/':
        return make_token(Token::TokenType::TOKEN_SLASH);
    case '*':
        return make_token(Token::TokenType::TOKEN_STAR);
    case '!':
        return make_token(match('=') ? Token::TokenType::TOKEN_BANG_EQUAL : Token::TokenType::TOKEN_BANG);
    case '=':
        return make_token(match('=') ? Token::TokenType::TOKEN_EQUAL_EQUAL : Token::TokenType::TOKEN_EQUAL);
    case '<':
        return make_token(match('=') ? Token::TokenType::TOKEN_LESS_EQUAL : Token::TokenType::TOKEN_LESS);
    case '>':
        return make_token(match('=') ? Token::TokenType::TOKEN_GREATER_EQUAL : Token::TokenType::TOKEN_GREATER);
    case '"':
        return string();
        //case '\'':
    }
    return Token(Token::TokenType::TOKEN_ERROR, TokenPosition(), "Unexpected character: \"" + std::string(1, c) + "\".");
}