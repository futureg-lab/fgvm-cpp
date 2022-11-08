#include "FGLexer.h"

FGScript::FGLexer::FGLexer(std::string source, std::string filepath)
    : Lexer(source, filepath)
{
}

std::vector<fgvm::Token> FGScript::FGLexer::tokenize()
{
    std::vector<fgvm::Token> tokens;

    nextChar();

    while (!hasEnded()) {
        if (current_char == ' ') {
            nextChar();
            continue;
        }

        // string
        if (current_char == '"') {
            std::string str = makeString();
            tokens.push_back(createToken(STRING, str));
            continue;
        }

        // number
        if (Lexer::isNum(current_char)) {
            std::string str = makeNumber();
            tokens.push_back(createToken(NUMBER, str));
            continue;
        }

        // literal

        if (Lexer::isStandardExpression(current_char)) {
            std::string str = makeStandardExpression();
            tokens.push_back(createToken(LITERAL_EXPR, str));
            continue;
        }

        // fallback
        if (!hasEnded()) {
            tokens.push_back(createTokenUnknown());
        }

        nextChar();
    }

    tokens.push_back(createToken(EOFILE, std::string(&current_char)));
    return tokens;
}


fgvm::Token FGScript::FGLexer::createToken(TokenType type, std::string value)
{
    fgvm::Token token((int)type, value, cursor, FGLexer::describe(type));
    return token;
}

fgvm::Token FGScript::FGLexer::createTokenUnknown()
{
    fgvm::Token token(UNKNOWN, current_char, cursor, FGLexer::describe(UNKNOWN));
    return token;
}


std::string FGScript::FGLexer::describe(int type_token)
{
    std::unordered_map<int, std::string> description = {
        {TokenType::UNKNOWN, "unknown token"},
        {TokenType::STRING, "string"},
        {TokenType::NUMBER, "number"},
        {TokenType::LITERAL_EXPR, "literal"},
        {TokenType::EOFILE, "EOF"}
    };
    if (description.find(type_token) != description.end())
        return description[type_token];
    return "???";
}