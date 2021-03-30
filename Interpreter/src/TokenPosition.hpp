#pragma once

#include <string>

class TokenPosition
{
private:
    std::string file;
    unsigned int line;
    unsigned int column;

    friend std::ostream &operator<<(std::ostream &out, const TokenPosition &value);

public:
    TokenPosition(std::string file = "<no_file>", unsigned int line = 0, unsigned int column = 0);

    std::string get_file()const;
    unsigned int get_line()const;
    unsigned int get_column()const;
};
