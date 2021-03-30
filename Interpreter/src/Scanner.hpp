#pragma once

#include "Token.hpp"

#include <string>
#include <vector>

class Scanner
{
private:
    bool is_at_end();
    char advance();
    bool match(char expected);
    void skip_whitespace();
    char peek();
    char peek_next();
    Token string();
    bool is_digit(char character);
    Token number();
    bool is_alpha(char character);
    Token identifier();
    Token::TokenType identifier_type();
    Token make_token(Token::TokenType type);
    Token::TokenType check_keyword(unsigned int start, unsigned int length, const std::string &rest, Token::TokenType type);

    std::string src;
    const std::string file_name;
    unsigned int line;
    unsigned int column;
    unsigned int current;
    unsigned int start;

public:
    Scanner(const std::string &file_name, const std::string &src);
    Scanner(const std::string &file_name);
    Token scanToken();
};
