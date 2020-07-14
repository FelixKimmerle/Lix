#include "Stmt.hpp"

Stmt::Stmt(unsigned int p_uiLine) : m_uiLine(p_uiLine)
{
}

Stmt::~Stmt()
{
}

unsigned int Stmt::getLine()
{
    return m_uiLine;
}