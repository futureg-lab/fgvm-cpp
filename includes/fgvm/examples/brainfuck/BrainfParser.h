#pragma once

#include <iostream>

#include "../../core/analytic-tools/Parser.h"
#include "../../core/values/Value.h"
#include "../../core/generator/Module.h"
#include "../../core/generator/CodeBuilder.h"

namespace Brainf_ck {
	struct BodyAST;
	struct MemAST;
	struct OpAST;
	struct LoopAST;

	
	class BrainfParser : public fgvm::Parser {
	public:
		std::unique_ptr<fgvm::Module> module_owner;
		std::unique_ptr<fgvm::CodeBuilder> builder;

		std::unique_ptr<BodyAST> parse();
		std::unique_ptr<BodyAST> singlePass();

		BrainfParser(std::vector<fgvm::Token>& tokens);
		std::string compileToIntermediateCode() override;
	};


	struct AST {
		virtual fgvm::Value* codegen() = 0;
	};

	struct BodyAST : public AST {
		std::vector<std::unique_ptr<BodyAST>> expressions;
		fgvm::Value* codegen() override;
	};

	struct MemAST : public AST {
	private:
		bool go_left = false;
	public:
		MemAST(bool go_left);
		fgvm::Value* codegen() override;
	};

	struct OpAST : public AST {
	private:
		bool do_sub = false;
	public:
		OpAST(bool do_sub);
		fgvm::Value* codegen() override;
	};

	struct LoopAST : public AST {
		std::unique_ptr<BodyAST> body;
		fgvm::Value* codegen() override;
	};
}