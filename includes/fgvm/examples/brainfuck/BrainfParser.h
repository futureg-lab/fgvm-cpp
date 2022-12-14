#pragma once

#include <iostream>

#include "../../core/analytic-tools/Lexer.h"
#include "../../core/analytic-tools/Parser.h"
#include "../../core/generator/Module.h"
#include "../../core/generator/CodeBuilder.h"

#include "../../core/generator/ir-generator/IRSourceGenerator.h"
#include "../../core/generator/NameGenerator.h"


#include "BrainfLexer.h"
#include <memory>

namespace Brainf_ck {
	struct AST;
	struct BodyAST;
	struct MemAST;
	struct OpAST;
	struct LoopAST;
	struct IoAST;

	class BrainfParser : public fgvm::Parser {
	private:
		// variable name generator
		std::unique_ptr<fgvm::NameGenerator> var = std::make_unique<fgvm::NameGenerator>();
		// ir code generator
		std::unique_ptr<IRSourceGenerator> generator = std::make_unique<IRSourceGenerator>();

		// owns all statements
		std::unique_ptr<fgvm::Module> module_owner = std::make_unique<fgvm::Module>();
		// generates the statements
		std::unique_ptr<fgvm::CodeBuilder> builder = std::make_unique<fgvm::CodeBuilder>(module_owner.get());

		fgvm::Value* main_ptr = nullptr;

		std::shared_ptr<BodyAST> parse();
		std::shared_ptr<AST> singlePass();
	public:
		fgvm::StatementSequence* program = builder->createStmtSequence();
		

		BrainfParser(std::vector<fgvm::Token>& tokens);

		// visitor pattern
		fgvm::Statement* visit(std::shared_ptr<AST> ast);
		fgvm::Statement* visit(std::shared_ptr<BodyAST> ast);
		fgvm::Statement* visit(std::shared_ptr<MemAST> ast);
		fgvm::Statement* visit(std::shared_ptr<OpAST> ast);
		fgvm::Statement* visit(std::shared_ptr<LoopAST> ast);
		fgvm::Statement* visit(std::shared_ptr<IoAST> ast);

		std::string compileToIntermediateCode() override;
	private:
		std::shared_ptr<LoopAST> handleLoopBlock();
	};

	enum ASTType { UNDEFINED_AST = -1, BODY_AST, MEM_ACTION_AST, OP_ACTION_AST, LOOP_AST, IO_AST };
	
	struct AST {
		ASTType type = UNDEFINED_AST;
	};

	struct BodyAST : public AST {
		std::vector<std::shared_ptr<AST>> expressions;
		BodyAST() {
			type = BODY_AST;
		}
		void addExpr(std::shared_ptr<AST> expr) {
			expressions.push_back(expr);
		}
		size_t exprCount() const {
			return expressions.size();
		}
	};

	struct MemAST : public AST {
		bool go_left = false;
		MemAST(bool go_left) : go_left(go_left) {
			type = MEM_ACTION_AST;
		}
	};

	struct OpAST : public AST {
		bool do_sub = false;
		OpAST(bool do_sub) : do_sub(do_sub) {
			type = OP_ACTION_AST;
		}
	};

	struct LoopAST : public AST {
		std::shared_ptr<BodyAST> body;
		LoopAST() {
			type = LOOP_AST;
			body = std::make_shared<BodyAST>();
		}
	};

	struct IoAST : public AST {
		bool do_print = false;
		IoAST(bool do_print) {
			type = IO_AST;
			this->do_print = do_print;
		}
	};
}