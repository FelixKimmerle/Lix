#include "Stmt.hpp"

Stmt::Stmt(TokenPosition position) : position(position)
{
}

TokenPosition Stmt::get_position()
{
    return position;
}
