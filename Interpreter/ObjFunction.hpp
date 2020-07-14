#pragma once
#include "Chunk.hpp"
class ObjFunction
{
private:
    unsigned int m_uiArity;
    Chunk m_Chunk;
    std::string m_sName;
public:
    ObjFunction(/* args */);
    ~ObjFunction();
    Chunk * getChunk();
};

