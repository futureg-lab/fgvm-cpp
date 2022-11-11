#include "Token.h"

#include "../utils/IRUtils.h"

void fgvm::Token::define(int type, std::string value, CursorPosition cursor, std::string description)
{
    this->type = type;
    this->value = value;
    this->cursor = cursor;
    this->description = description;
}

fgvm::Token::Token(int type, std::string value, CursorPosition cursor, std::string description)
{
    define(type, value, cursor, description);
}

fgvm::Token::Token(int type, char value, CursorPosition cursor, std::string description)
{
    std::string str_value = {value};
    define(type, str_value, cursor, description);
}

std::string fgvm::Token::to_string()
{
    std::string str = "token \"{0}\", type = {1} {2}, start at {3}";
    return IRUtils::format(str, {value, std::to_string(type), description, std::to_string(cursor.pos)});
}
