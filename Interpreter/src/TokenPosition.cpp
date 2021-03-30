#include "TokenPosition.hpp"

#include <ostream>

TokenPosition::TokenPosition(std::string file, unsigned int line, unsigned int column) : file(file), line(line), column(column)
{
}

std::ostream &operator<<(std::ostream &out, const TokenPosition &value)
{
    out << value.file << ":" << value.line << ":" << value.column;
    return out;
}

std::string TokenPosition::get_file() const
{
    return file;
}
unsigned int TokenPosition::get_line() const
{
    return line;
}
unsigned int TokenPosition::get_column() const
{
    return column;
}