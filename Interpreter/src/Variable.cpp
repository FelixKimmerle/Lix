#include "Variable.hpp"

Variable::Variable(LixDatatype type, std::string name, unsigned int depth, TokenPosition position) : type(type),
                                                                                                     name(name),
                                                                                                     depth(depth),
                                                                                                     position(position)
{
}

std::string Variable::get_name()
{
    return name;
}

LixDatatype Variable::get_type()
{
    return type;
}

unsigned int Variable::get_depth()
{
    return depth;
}

TokenPosition Variable::get_position()
{
    return position;
}