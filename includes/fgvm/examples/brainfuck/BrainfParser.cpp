#include "BrainfParser.h"


using namespace Brainf_ck;

BodyAST* Brainf_ck::BrainfParser::parse()
{
    return nullptr;
}

AST* Brainf_ck::BrainfParser::singlePass()
{
    // int type = currentToken().type;

    AST* ast = nullptr;

    switch (currentToken().type) {
    case TokenType::MEM_LEFT:
        ast = new MemAST(true); // true == go_left
        break;
    case TokenType::MEM_RIGHT:
        ast = new MemAST(false); // false == go_left
        break;
    case TokenType::PLUS:
        ast = new OpAST(false); // true == do_sub
        break;
    case TokenType::MINUS:
        ast = new OpAST(true); // false == do_sub
        break;
    case TokenType::LOOP_OPEN: // ] will automatically be handled
        ast = handleLoopBlock();
    case TokenType::UNKNOWN:
        break;
    }

    return ast;
}

Brainf_ck::BrainfParser::BrainfParser(std::vector<fgvm::Token>& tokens)
    : Parser(tokens)
{
    this->module_owner = std::make_unique<fgvm::Module>();
    this->builder = std::make_unique<fgvm::CodeBuilder>(module_owner.get());
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(BodyAST* ast)
{
    return nullptr;
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(MemAST* ast)
{
    return nullptr;
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(OpAST* ast)
{
    return nullptr;
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(LoopAST* ast)
{
    return nullptr;
}

// 
std::string Brainf_ck::BrainfParser::compileToIntermediateCode()
{
    return std::string();
}

LoopAST* Brainf_ck::BrainfParser::handleLoopBlock()
{
    return nullptr;
}
