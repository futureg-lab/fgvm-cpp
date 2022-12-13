#include "BrainfLexer.h"

Brainf_ck::BrainfLexer::BrainfLexer(std::string source, std::string filepath)
	: Lexer(source, filepath)
{
}

std::vector<fgvm::Token> Brainf_ck::BrainfLexer::tokenize()
{
    std::unordered_map<char, TokenType> unique_char_tk = {
        {'<', MEM_LEFT},
        {'>', MEM_RIGHT},
        {'-', MINUS},
        {'+', PLUS},
        {'[', LOOP_OPEN},
        {']', LOOP_CLOSE},
        {',', STD_IN},
        {'.', STD_OUT}
    };
    std::vector<fgvm::Token> tokens;

    nextChar();
    while (!hasEnded()) {
        if (current_char == ' ' || current_char == '\n' || current_char == '\r') {
            nextChar();
            continue;
        }

        if (unique_char_tk.find(current_char) != unique_char_tk.end()) {
            auto type = unique_char_tk[current_char];
            tokens.push_back(createToken(type, current_char));
            nextChar();
            continue;
        }

        // fallback
        nextChar();
    }
    
    tokens.push_back(createToken(END_OF_FILE, current_char));
	
    return tokens;
}

std::string Brainf_ck::BrainfLexer::describe(int type_token)
{
    std::unordered_map<int, std::string> description = {
        {MINUS, "value decrement"},
        {PLUS, "value increment"},
        {STD_IN, "stdin"},
        {STD_OUT, "stdout"},
        {LOOP_OPEN, "loop opened"},
        {LOOP_CLOSE, "loop closed"},
        {MEM_LEFT, "memory go left"},
        {MEM_RIGHT, "memory go right"},
        {END_OF_FILE, "end of file"}
    };
    if (description.find(type_token) != description.end())
        return description[type_token];
    return "???";
}

fgvm::Token Brainf_ck::BrainfLexer::createToken(TokenType type, char value)
{
    fgvm::Token token((int)type, value, cursor, BrainfLexer::describe(type));
    return token;
}

fgvm::Token Brainf_ck::BrainfLexer::createTokenUnknown()
{
    return createToken(UNKNOWN, current_char);
}