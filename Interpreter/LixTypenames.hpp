#pragma once

#include <cstdint>
#include <string>

typedef bool Lix_Bool;
typedef uint8_t Lix_Byte;
typedef int16_t Lix_ShortInt;
typedef int32_t Lix_Int;
typedef float Lix_Float;
typedef double Lix_Double;
typedef int64_t Lix_LongInt;

#ifdef _WIN32 //need this typedefs for windows
typedef uint16_t u_int16_t;
typedef uint16_t u_int8_t;

#endif

class LixDatatype
{
public:
    enum class LixPod : uint8_t
    {
        LD_Byte,
        LD_ShortInt,
        LD_Int,
        LD_Float,
        LD_Double,
        LD_LongInt,
        LD_Bool,
    };

private:
    /* data */
public:
    LixDatatype(/* args */);
    ~LixDatatype();
};

LixDatatype::LixDatatype(/* args */)
{
}

LixDatatype::~LixDatatype()
{
}

LixDatatype maxType(LixDatatype left, LixDatatype right);
std::string lixDatatypeToString(LixDatatype p_Type);
unsigned int getSize(LixDatatype p_Type);