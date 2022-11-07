#include "Lexer.h"

void fgvm::Lexer::nextChar()
{
    cursor.pos++;
    if (cursor.pos >= (int)source.size())
        current_char = '\0';
    else
        current_char = source[cursor.pos];

    if (current_char == '\n') {
        cursor.line++;
        cursor.col = 0;
        nextChar();
    }
    else {
        cursor.col++;
    }

}

char fgvm::Lexer::peekNextChar() const
{
    return cursor.pos + 1 >= (int)source.size() ? '\0' : source[cursor.pos + 1];
}

std::string fgvm::Lexer::makeString()
{
    std::string str = "";
    nextChar(); // ignore first '"'
    while (current_char != '"') {
        str += current_char;
        nextChar();
        if (current_char == '\0')
            throw Lexer::tokenError("interminated string", cursor, filepath);
    }
    nextChar();
    return str;
}

std::string fgvm::Lexer::makeNumber()
{
    std::string str = "";
    bool got_a_dot = false;
    while (Lexer::isNum(current_char) || current_char == '.') {
        if (current_char == '.') {
            if (got_a_dot)
                throw Lexer::tokenError("double \".\" encountered", cursor, filepath);
            got_a_dot = true;
        }
        str += current_char;
        nextChar();
    }
    return str;
}

std::string fgvm::Lexer::makeStandardExpression()
{
    std::string str = "";
    while (Lexer::isStandardExpression(current_char)) {
        str += current_char;
        nextChar();
    }
    return str;
}

fgvm::Lexer::Lexer(std::string source, std::string filepath)
    : source(source), filepath(filepath)
{
}

std::vector<fgvm::Token> fgvm::Lexer::tokenize()
{
    std::vector<Token> tokens;
    nextChar();
    while (current_char != '\0') {
        Token token(0, current_char, cursor, "no description");
        tokens.push_back(token);
        nextChar();
    }
    return tokens;
}

bool fgvm::Lexer::isNum(char character)
{
    return (bool) isdigit(character);
}

bool fgvm::Lexer::isAlpha(char character)
{
    return (bool) isalpha(character);
}

bool fgvm::Lexer::isStandardExpression(char character)
{
    return isalnum(character) || character == '_';
}

std::logic_error fgvm::Lexer::tokenError(std::string reason, CursorPosition& pos, std::string filepath)
{
    std::string msg = IRUtils::format(
        "{0} ... at line {1}, col {2} ({3})", 
        { reason, std::to_string(pos.line), std::to_string(pos.col), filepath }
    );
    return FGError::notExpected(msg);
}
