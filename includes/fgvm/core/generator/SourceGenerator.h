#pragma once

#include "../StatementSequence.h"

#include "../values/Value.h"
#include "../values/FunctionCallValue.h"
#include "../values/FunctionCustomCallValue.h"
#include "../values/SARValue.h"
#include "../values/SARRefValue.h"
#include "../values/FArgValue.h"

#include "../blocs/Bloc.h"
#include "../blocs/FunctionDef.h"
#include "../blocs/ConditionalBr.h"
#include "../blocs/Loop.h"

#include "../utils/IRUtils.h"


class SourceGenerator {
private:

public:

	// any statement
	std::string generate(fgvm::Statement* statement);

	// values
	// any value
	std::string generate(fgvm::Value* value);
	virtual std::string generate(fgvm::FArgValue* value) = 0;
	virtual std::string generate(fgvm::FunctionCustomCallValue* value) = 0;
	virtual std::string generate(fgvm::RetValue* value) = 0;
	virtual std::string generate(fgvm::SARRefValue* value) = 0;
	virtual std::string generate(fgvm::SARValue* value) = 0;



	// Statement sequence
	virtual std::string generate(fgvm::StatementSequence* sequence) = 0;
	// bloc statements
	virtual std::string generate(fgvm::Bloc* stmt) = 0;
	virtual std::string generate(fgvm::ConditionalBr* stmt) = 0;
	virtual std::string generate(fgvm::FunctionDef* stmt) = 0;
	virtual std::string generate(fgvm::Loop* stmt) = 0;
};