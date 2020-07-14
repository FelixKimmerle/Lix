#pragma once
#include <string>
#include "LixTypenames.hpp"
class Variable
{
private:
    std::string m_sName;
    unsigned int m_uiDepth;
    LixDatatype m_Type;
    unsigned int m_uiLine;

public:
    Variable(LixDatatype p_Type, std::string p_sName, unsigned int p_uiDepth, unsigned int p_uiLine);
    ~Variable();
    std::string getName();
    unsigned int getDepth();
    LixDatatype getType();
    unsigned int getLine();
};
