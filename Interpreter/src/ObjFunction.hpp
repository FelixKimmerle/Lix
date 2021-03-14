#pragma once
#include "Chunk.hpp"
class ObjFunction
{
private:
    unsigned int m_uiArity;
    Chunk m_Chunk;
    std::string m_sName;
public:
    ObjFunction(const std::string &p_sName, unsigned int p_uiArity);
    ~ObjFunction();
    Chunk * getChunk();

    std::string getName()const;
    unsigned int getArity()const;
};

