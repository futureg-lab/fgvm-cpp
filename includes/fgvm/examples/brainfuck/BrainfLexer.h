#pragma once

#include <iostream>

#include "../../core/analytic-tools/Lexer.h"
#include <unordered_map>

namespace Brainf_ck {
    enum TokenType {
        UNKNOWN = -1,
        END_OF_FILE = 0,

        PLUS, // -
        MINUS, // -
        STD_IN, // ,
        STD_OUT, // .
        MEM_LEFT, // <
        MEM_RIGHT, // >

        LOOP_OPEN, // [
        LOOP_CLOSE, // ]
    };

    class BrainfLexer : public fgvm::Lexer {
    public:
        BrainfLexer(std::string source, std::string filepath);
        std::vector<fgvm::Token> tokenize() override;

        static std::string describe(int type_token);
    private:
        fgvm::Token createToken(TokenType type, char value);
        fgvm::Token createTokenUnknown();
    };
}