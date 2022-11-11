#include "Parser.h"

#include "../utils/FGError.h"

fgvm::Parser::Parser(std::vector<Token>& tokens)
    : tokens(tokens)
{
}

std::string fgvm::Parser::compileToIntermediateCode()
{
    return std::string();
}

fgvm::Token fgvm::Parser::tokenAt(size_t pos)
{
    if (tokens.size() == 0)
        throw FGError::notExpected("token count is 0");
    pos = std::max((size_t)0, std::min((size_t)pos, tokens.size() - 1));
    return tokens[pos];
}

fgvm::Token fgvm::Parser::peekNextToken()
{
    return tokenAt(cursor_pos + 1);
}

fgvm::Token fgvm::Parser::nextToken()
{
    return tokenAt(cursor_pos++); // we start at 0, not -1
}

fgvm::Token fgvm::Parser::currentToken()
{
    return tokenAt(cursor_pos);
}
