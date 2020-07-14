#include <array>

namespace Converter
{
template<class T>
std::array<uint8_t, sizeof(T)> *encode(T *Value);

template<class T>
T *decode(std::array<uint8_t, sizeof(T)> *Value);

} // namespace Converter
