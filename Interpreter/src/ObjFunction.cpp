#include "ObjFunction.hpp"

Chunk *ObjFunction::getChunk()
{
    return &this->m_Chunk;
}
ObjFunction::ObjFunction(const std::string &p_sName, unsigned int p_uiArity) : m_sName(p_sName), m_uiArity(p_uiArity)
{
}

ObjFunction::~ObjFunction()
{
}
std::string ObjFunction::getName() const
{
    return m_sName;
}

unsigned int ObjFunction::getArity() const
{
    return m_uiArity;
}