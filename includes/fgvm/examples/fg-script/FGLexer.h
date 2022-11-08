#pragma once

#include "../../core/analytic-tools/Lexer.h"
#include <unordered_map>


namespace FGScript {
    enum TokenType {
        UNKNOWN = -1,
        NUMBER,
        STRING,
        EOFILE,
        LITERAL_EXPR
    };

    class FGLexer : public fgvm::Lexer {
    public:
        FGLexer(std::string source, std::string filepath);
        std::vector<fgvm::Token> tokenize() override;

        static std::string describe(int type_token);
    private:
        fgvm::Token createToken(TokenType type, std::string description);
        fgvm::Token createTokenUnknown();
    };
}
