#include "BrainfParser.h"


using namespace Brainf_ck;

std::unique_ptr<BodyAST> Brainf_ck::BrainfParser::parse()
{
	return std::unique_ptr<BodyAST>();
}

std::unique_ptr<BodyAST> Brainf_ck::BrainfParser::singlePass()
{
    std::unique_ptr<BodyAST> ast = std::make_unique<BodyAST>();
    /*
    const {type} = this.currentToken();
    switch (type) {
    case TokenID.MEM_LEFT:
        ast = new MemAST(true); // true == go_left
        break;
    case TokenID.MEM_RIGHT:
        ast = new MemAST(false); // false == go_left
        break;
    case TokenID.PLUS:
        ast = new OpAST(true); // true == do_sub
        break;
    case TokenID.MINUS:
        ast = new OpAST(false); // false == do_sub
        break;
    case TokenID.LOOP_OPEN: // ] will automatically be handled
        ast = this.handleLoopBlock();
    case TokenID.UNKNOWN:
        break;
    }
    return ast;*/
	return std::unique_ptr<BodyAST>();
}

Brainf_ck::BrainfParser::BrainfParser(std::vector<fgvm::Token>& tokens)
	: Parser(tokens)
{
    this->module_owner = std::make_unique<fgvm::Module>();
    this->builder = std::make_unique<fgvm::CodeBuilder>(module_owner.get());
}

// 
std::string Brainf_ck::BrainfParser::compileToIntermediateCode()
{
	return std::string();
}

fgvm::Value* Brainf_ck::BodyAST::codegen()
{
    return nullptr;
}

// memory
Brainf_ck::MemAST::MemAST(bool go_left)
{
    this->go_left = go_left;
}

fgvm::Value* Brainf_ck::MemAST::codegen()
{
    return nullptr;
}

// Op
Brainf_ck::OpAST::OpAST(bool do_sub)
{
    this->do_sub = do_sub;
}

fgvm::Value* Brainf_ck::OpAST::codegen()
{
    return nullptr;
}

// Loop
fgvm::Value* Brainf_ck::LoopAST::codegen()
{
    return nullptr;
}
