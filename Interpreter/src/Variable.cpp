#include "Variable.hpp"

Variable::Variable(LixDatatype p_Type, std::string p_sName, unsigned int p_uiDepth, unsigned int p_uiLine)
{
    m_Type = p_Type;
    m_sName = p_sName;
    m_uiDepth = p_uiDepth;
    m_uiLine = p_uiLine;
}

Variable::~Variable()
{
}

std::string Variable::getName()
{
    return m_sName;
}

LixDatatype Variable::getType()
{
    return m_Type;
}

unsigned int Variable::getDepth()
{
    return m_uiDepth;
}

unsigned int Variable::getLine()
{
    return m_uiLine;
}