#include "Expr.hpp"

Expr::Expr(unsigned int p_uiLine) : m_uiLine(p_uiLine)
{
}

unsigned int Expr::getLine()
{
    return m_uiLine;
}