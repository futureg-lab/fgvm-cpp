#pragma once

#include <vector>
#include <memory>
#include "../types/Type.h"
#include "../utils/FGError.h"

#include "../values/Value.h"
#include "../values/FunctionCallValue.h"
#include "../values/SARValue.h"

#include "Module.h"

class CodeBuilder {
public:
	fgvm::Module* module_container = nullptr;

	CodeBuilder(fgvm::Module* module_container);
	~CodeBuilder();

	fgvm::Value* createValue(std::string name, fgvm::Type* content);
	fgvm::Value* createAdd(std::string name, fgvm::Value* L, fgvm::Value* R);
};