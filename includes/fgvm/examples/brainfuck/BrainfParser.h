#pragma once

#include <iostream>

#include "../../core/analytic-tools/Parser.h"
#include "../../core/generator/Module.h"
#include "../../core/generator/CodeBuilder.h"

#include "BrainfLexer.h"

#include <memory>

namespace Brainf_ck {
	struct AST;
	struct BodyAST;
	struct MemAST;
	struct OpAST;
	struct LoopAST;


	class BrainfParser : public fgvm::Parser {
	public:
		std::unique_ptr<fgvm::Module> module_owner;
		std::unique_ptr<fgvm::CodeBuilder> builder;

		BodyAST* parse();
		AST* singlePass();

		BrainfParser(std::vector<fgvm::Token>& tokens);


		// visitor pattern
		fgvm::Statement* visit(BodyAST* ast);
		fgvm::Statement* visit(MemAST* ast);
		fgvm::Statement* visit(OpAST* ast);
		fgvm::Statement* visit(LoopAST* ast);

		std::string compileToIntermediateCode() override;
	private:
		LoopAST* handleLoopBlock();
	};


	struct AST { };

	enum ASTType { BODY_AST, MEM_ACTION_AST, OP_ACTION_AST, LOOP_AST };

	struct BodyAST : public AST {
		std::vector<std::unique_ptr<BodyAST>> expressions;
		ASTType type = BODY_AST;
		BodyAST() {}
	};

	struct MemAST : public AST {
		bool go_left = false;
		ASTType type = MEM_ACTION_AST;
		MemAST(bool go_left) : go_left(go_left) {}
	};

	struct OpAST : public AST {
		bool do_sub = false;
		ASTType type = OP_ACTION_AST;
		OpAST(bool do_sub) : do_sub(do_sub) {}
	};

	struct LoopAST : public AST {
		ASTType type = LOOP_AST;
		std::unique_ptr<BodyAST> body;
	};
}