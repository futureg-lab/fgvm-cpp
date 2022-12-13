#pragma once


#include "../types/Type.h"
#include "../utils/FGError.h"

#include "../values/Value.h"
#include "../values/FunctionCallValue.h"
#include "../values/SARValue.h"
#include "../values/SARRefValue.h"
#include "../values/FArgValue.h"

#include "Module.h"

#include "../blocs/Bloc.h"
#include "../blocs/FunctionDef.h"
#include "../blocs/ConditionalBr.h"
#include "../blocs/Loop.h"
#include "../StatementSequence.h"

#include <vector>
#include <memory>

namespace fgvm {
	class CodeBuilder {
	private:
		fgvm::Value* createBinaryFunc(std::string fcall_name, std::string name, fgvm::Value* L, fgvm::Value* R);
		fgvm::Value* createUnaryFunc(std::string fcall_name, std::string name, fgvm::Value* input);
		void registerToModuleObjectPool(fgvm::Statement* value);
	public:
		fgvm::Module* module_container = nullptr;

		CodeBuilder(fgvm::Module* module_container);
		~CodeBuilder();


		void SSRNamePass(fgvm::StatementSequence* sequence);

		fgvm::SARValue* createValue(std::string name, fgvm::Type content);
		fgvm::FArgValue* createArg(std::string name, fgvm::EType type_hint_id);

		// handling memory
		// %x = 
		fgvm::SARRefValue* createGetAddrOf(std::string name, fgvm::Value* value);
		fgvm::Value* createAlloc(std::string name, fgvm::Value* mem_size);
		fgvm::Value* createSetValAddr(std::string name, fgvm::Value* addr, fgvm::Value* value);
		fgvm::Value* createGetValAddr(std::string name, fgvm::SARRefValue* ref);
		fgvm::Value* createGetValAddr(std::string name, fgvm::Value* ref, fgvm::EType type_output_hint);

		fgvm::RetValue* createReturn(fgvm::Value* value);

		// basic functions

		fgvm::Value* createAdd(std::string name, fgvm::Value* L, fgvm::Value* R);
		fgvm::Value* createSub(std::string name, fgvm::Value* L, fgvm::Value* R);
		fgvm::Value* createDiv(std::string name, fgvm::Value* L, fgvm::Value* R);
		fgvm::Value* createMult(std::string name, fgvm::Value* L, fgvm::Value* R);
		fgvm::Value* createIncr(fgvm::Value* value);
		fgvm::Value* createDecr(fgvm::Value* value);

		// comparison
		// Equal
		fgvm::Value* createCompEQ(std::string name, fgvm::Value* L, fgvm::Value* R);
		// Not equal
		fgvm::Value* createCompNOTEQ(std::string name, fgvm::Value* L, fgvm::Value* R);
		// Great than or equal
		fgvm::Value* createCompGTEQ(std::string name, fgvm::Value* L, fgvm::Value* R);
		// Less than or equal
		fgvm::Value* createCompLTEQ(std::string name, fgvm::Value* L, fgvm::Value* R);
		// Less than
		fgvm::Value* createCompLT(std::string name, fgvm::Value* L, fgvm::Value* R);
		// Great than
		fgvm::Value* createCompGT(std::string name, fgvm::Value* L, fgvm::Value* R);

		// bloc
		fgvm::FunctionDef* createFunc(std::string name, std::vector<fgvm::FArgValue*> args, fgvm::Bloc* bloc, fgvm::EType exp_ret_type);
		fgvm::StatementSequence* createStmtSequence();
		fgvm::Bloc* createBloc(std::string name);
		fgvm::ConditionalBr* createIF(fgvm::Value* condition, fgvm::Bloc* if_bloc, fgvm::Bloc* else_bloc);
		fgvm::Loop* createLoop(fgvm::Value* condition, fgvm::Bloc* bloc);

		// stdin and out
		fgvm::Value* createStdout(std::string name, fgvm::Value* value);
		fgvm::Value* createStderr(std::string name, fgvm::Value* value);
		fgvm::Value* createStdin(std::string name, fgvm::EType type_hint);
	};
}