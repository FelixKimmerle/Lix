#pragma once

#include "LixTypenames.hpp"
#include "TokenPosition.hpp"

#include <string>

class Variable
{
private:
    std::string name;
    unsigned int depth;
    LixDatatype type;
    TokenPosition position;

public:
    Variable(LixDatatype type, std::string name, unsigned int depth, TokenPosition position);
    std::string get_name();
    unsigned int get_depth();
    LixDatatype get_type();
    TokenPosition get_position();
};
