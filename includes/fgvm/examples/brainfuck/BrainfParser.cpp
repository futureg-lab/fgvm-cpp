#include "BrainfParser.h"


using namespace Brainf_ck;


// setup

std::shared_ptr<BodyAST> Brainf_ck::BrainfParser::parse()
{
    std::shared_ptr<BodyAST> body = std::make_shared<BodyAST>();
    while (currentToken().type != TokenType::END_OF_FILE) {
        std::shared_ptr<AST> ast = singlePass();
        if (ast)
            body->addExpr((ast));
        nextToken();
    }
    return body;
}

std::shared_ptr<AST> Brainf_ck::BrainfParser::singlePass()
{
    std::shared_ptr<AST> ast = nullptr;
    switch (currentToken().type) {
    case TokenType::MEM_LEFT:
        ast = std::make_shared<MemAST>(true); // true == go_left
        break;
    case TokenType::MEM_RIGHT:
        ast = std::make_shared<MemAST>(false); // false == go_left
        break;
    case TokenType::PLUS:
        ast = std::make_shared<OpAST>(false); // true == do_sub
        break;
    case TokenType::MINUS:
        ast = std::make_shared<OpAST>(true); // false == do_sub
        break;
    case TokenType::LOOP_OPEN: // ] will be automatically handled
        ast = handleLoopBlock();
        break;
    case TokenType::STD_IN:
        ast = std::make_shared<IoAST>(false); // false == do getch()
        break;
    case TokenType::STD_OUT:
        ast = std::make_shared<IoAST>(true);
        break;
    }
    return ast;
}

Brainf_ck::BrainfParser::BrainfParser(std::vector<fgvm::Token>& tokens)
    : Parser(tokens)
{
    auto mem_size = builder->createValue(var->get("mem_size"), new fgvm::U32(255));
    main_ptr = builder->createAlloc(var->get("main_ptr"), mem_size);
    program->add(mem_size);
    program->add(main_ptr);
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(std::shared_ptr<AST> ast)
{
    fgvm::Statement* statement = nullptr;
    
    switch (ast->type) {
    case ASTType::BODY_AST:
        statement = visit(std::static_pointer_cast<BodyAST>(ast));
        break;
    case ASTType::LOOP_AST:
        statement = visit(std::static_pointer_cast<LoopAST>(ast));
        break;
    case ASTType::MEM_ACTION_AST:
        statement = visit(std::static_pointer_cast<MemAST>(ast));
        break;
    case ASTType::OP_ACTION_AST:
        statement = visit(std::static_pointer_cast<OpAST>(ast));
        break;
    case ASTType::IO_AST:
        statement = visit(std::static_pointer_cast<IoAST>(ast));
        break;
    case ASTType::UNDEFINED_AST:
        throw FGError::notExpected("invalid expression id encountered");
    }

    return statement;
}


fgvm::Statement* Brainf_ck::BrainfParser::visit(std::shared_ptr<BodyAST> ast)
{
    fgvm::StatementSequence* seq = builder->createStmtSequence();
    for (auto& expr_ast : ast->expressions) {
        auto stmt = visit(expr_ast);
        if (stmt != nullptr)
            seq->add(stmt);
    }
    return seq;
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(std::shared_ptr<MemAST> ast)
{
    fgvm::Value* temp = nullptr;
    if (ast->go_left)
        temp = builder->createDecr(main_ptr);
    else
        temp = builder->createIncr(main_ptr);
    return temp;
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(std::shared_ptr<OpAST> ast)
{
    fgvm::StatementSequence* seq = builder->createStmtSequence();

    // get current value
    auto curr_val = builder->createGetValAddr(var->get("curr_val"), main_ptr, fgvm::EType::Uint8);
    seq->add(curr_val);
    
    // increment or decrement
    fgvm::Value* incr_or_decr = nullptr;
    if (ast->do_sub)
        incr_or_decr = builder->createDecr(curr_val);
    else
        incr_or_decr = builder->createIncr(curr_val);
    seq->add(incr_or_decr);

    // set current value
    auto set_val = builder->createSetValAddr(var->get("set_curr_val"), main_ptr, incr_or_decr);
    seq->add(set_val);


    return seq;
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(std::shared_ptr<LoopAST> ast)
{
    auto seq = builder->createStmtSequence();
    
    auto curr_val = builder->createGetValAddr(var->get("curr_val"), main_ptr, fgvm::EType::Uint8);
    seq->add(curr_val);

    auto loop_bloc = builder->createBloc(var->get("loop_bloc"));
    // should probably cache this value but whatever
    auto zero = builder->createValue(var->get("zero"), new fgvm::U8(0));
    seq->add(zero);
    auto cond = builder->createCompEQ(var->get("comp"), curr_val, zero);
    seq->add(cond);

    auto loop = builder->createLoop(cond, loop_bloc);
    // populate loop_bloc
    for (auto& expr : ast->body->expressions)
        loop_bloc->addStmt(visit(expr));
    seq->add(loop);

    return seq;
}

fgvm::Statement* Brainf_ck::BrainfParser::visit(std::shared_ptr<IoAST> ast)
{
    auto seq = builder->createStmtSequence();
    
    auto curr_val = builder->createGetValAddr(var->get("curr_val"), main_ptr, fgvm::EType::Uint8);
    seq->add(curr_val);

    if (ast->do_print) {
        seq->add(builder->createStdout(var->get("print"), curr_val));
    } else {
        auto print_or_scanf = builder->createStdin(var->get("scanf"), fgvm::EType::Uint8);
        auto temp = builder->createSetValAddr("set_curr_val", main_ptr, print_or_scanf);
        seq->add(print_or_scanf);
        seq->add(temp);
    }
    return seq;
}

// 
std::string Brainf_ck::BrainfParser::compileToIntermediateCode()
{
    std::shared_ptr<BodyAST> ast = parse();
    fgvm::Statement* stmt = visit(ast);

    auto seq = dynamic_cast<fgvm::StatementSequence*>(stmt);
    program->add(seq);

    return generator->generate(program);
}

std::shared_ptr<LoopAST> Brainf_ck::BrainfParser::handleLoopBlock()
{
    std::shared_ptr<LoopAST> loop = std::make_shared<LoopAST>();
    nextToken();
    while (currentToken().type != TokenType::LOOP_CLOSE) {
        // this will handle loops recursively
        auto ast = singlePass();
        if (ast)
            loop->body->addExpr(ast);
        nextToken();
        if (currentToken().type == TokenType::END_OF_FILE) {
            // premature end
            auto cursor = currentToken().cursor;
            throw FGError::notExpected("unclosed loop, ] expected at line " + std::to_string(cursor.line) + ", col " + std::to_string(cursor.col));
        }
    }
    return loop;
}
