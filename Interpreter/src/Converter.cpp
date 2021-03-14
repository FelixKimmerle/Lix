#include "Converter.hpp"
#include "LixTypenames.hpp"

namespace Converter
{

template <class T>
std::array<uint8_t, sizeof(T)> *encode(T *Value)
{
    return reinterpret_cast<std::array<uint8_t, sizeof(T)> *>(Value);
}
template <class T>
T *decode(std::array<uint8_t, sizeof(T)> *Value)
{
    return reinterpret_cast<T *>(Value);
}


template std::array<uint8_t, sizeof(Lix_Byte)> *encode<Lix_Byte>(Lix_Byte *Value);
template Lix_Byte *decode<Lix_Byte>(std::array<uint8_t, sizeof(Lix_Byte)> *Value);

template std::array<uint8_t, sizeof(Lix_ShortInt)> *encode<Lix_ShortInt>(Lix_ShortInt *Value);
template Lix_ShortInt *decode<Lix_ShortInt>(std::array<uint8_t, sizeof(Lix_ShortInt)> *Value);

template std::array<uint8_t, sizeof(Lix_Double)> *encode<Lix_Double>(Lix_Double *Value);
template Lix_Double *decode<Lix_Double>(std::array<uint8_t, sizeof(Lix_Double)> *Value);

template std::array<uint8_t, sizeof(Lix_Float)> *encode<Lix_Float>(Lix_Float *Value);
template Lix_Float *decode<Lix_Float>(std::array<uint8_t, sizeof(Lix_Float)> *Value);

template std::array<uint8_t, sizeof(Lix_Int)> *encode<Lix_Int>(Lix_Int *Value);
template Lix_Int *decode<Lix_Int>(std::array<uint8_t, sizeof(Lix_Int)> *Value);

template std::array<uint8_t, sizeof(Lix_LongInt)> *encode<Lix_LongInt>(Lix_LongInt *Value);
template Lix_LongInt *decode<Lix_LongInt>(std::array<uint8_t, sizeof(Lix_LongInt)> *Value);

template std::array<uint8_t, sizeof(Lix_Bool)> *encode<Lix_Bool>(Lix_Bool *Value);
template Lix_Bool *decode<Lix_Bool>(std::array<uint8_t, sizeof(Lix_Bool)> *Value);

template std::array<uint8_t, sizeof(Lix_Func)> *encode<Lix_Func>(Lix_Func *Value);
template Lix_Func *decode<Lix_Func>(std::array<uint8_t, sizeof(Lix_Func)> *Value);


} // namespace Converter
