#pragma once
#include <string>
class Token
{
public:
  enum class TokenType
  {
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_MINUS,
    TOKEN_PLUS,
    TOKEN_SEMICOLON,
    TOKEN_SLASH,
    TOKEN_STAR,

    // One or two character tokens.
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,
    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,

    // Literals.
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER_BYTE,
    TOKEN_NUMBER_SHORT,
    TOKEN_NUMBER_INT,
    TOKEN_NUMBER_FLOAT,
    TOKEN_NUMBER_DOUBLE,
    TOKEN_NUMBER_LONG,

    // Keywords.
    TOKEN_AND,
    TOKEN_CLASS,
    TOKEN_ELSE,
    TOKEN_FALSE,
    TOKEN_FOR,
    TOKEN_FUN,
    TOKEN_IF,
    TOKEN_NIL,
    TOKEN_OR,
    TOKEN_PRINT,
    TOKEN_RETURN,
    TOKEN_SUPER,
    TOKEN_THIS,
    TOKEN_TRUE,
    TOKEN_VAR,
    TOKEN_WHILE,
    TOKEN_BREAK,
    TOKEN_CONTINUE,

    TOKEN_INT,
    TOKEN_DOUBLE,
    TOKEN_FLOAT,
    TOKEN_BYTE,
    TOKEN_BOOL,
    TOKEN_SHORT,
    TOKEN_LONG,

    TOKEN_ERROR,
    TOKEN_EOF
  };

private:
  std::string m_sLexeme;
  unsigned int m_uiLine;
  TokenType m_TokenType;
  friend std::ostream &operator<<(std::ostream &out, const Token &value);

public:
  Token(TokenType p_TokenType, unsigned int p_uiLine, std::string p_sLexeme = "");
  Token();
  ~Token();
  TokenType getType();
  unsigned int getLine();
  std::string getLexeme();
};
