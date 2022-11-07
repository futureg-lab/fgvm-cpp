#pragma once

#include <vector>
#include <memory>
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

#include "../utils/IRUtils.h"

class CodeBuilder {
private:
	fgvm::Value* createBinaryFunc(std::string fcall_name, std::string name, fgvm::Value* L, fgvm::Value* R);
	void registerToModuleObjectPool(fgvm::Statement* value);
	void registerToSymbolTable(fgvm::Value* value);
public:
	fgvm::Module* module_container = nullptr;

	CodeBuilder(fgvm::Module* module_container);
	~CodeBuilder();

	fgvm::SARValue* createValue(std::string name, fgvm::Type* content);
	fgvm::FArgValue* createArg(std::string name, fgvm::EType type_hint_id);
	fgvm::SARRefValue* createRef(std::string name, fgvm::Value* value);
	fgvm::RetValue* createReturn(fgvm::Value* value);


	fgvm::Value* createAdd(std::string name, fgvm::Value* L, fgvm::Value* R);
	fgvm::Value* createSub(std::string name, fgvm::Value* L, fgvm::Value* R);
	fgvm::Value* createDiv(std::string name, fgvm::Value* L, fgvm::Value* R);
	fgvm::Value* createMult(std::string name, fgvm::Value* L, fgvm::Value* R);
	fgvm::Value* createDeref(std::string name, fgvm::SARRefValue* ref);

	fgvm::FunctionDef* createFunc(std::string name, std::vector<fgvm::FArgValue*> args, fgvm::Bloc* bloc, fgvm::EType exp_ret_type);
	fgvm::Bloc* createBloc(std::string name);
};