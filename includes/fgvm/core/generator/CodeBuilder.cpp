#include "CodeBuilder.h"

CodeBuilder::CodeBuilder(fgvm::Module* module_container)
{
	this->module_container = module_container;
}

CodeBuilder::~CodeBuilder()
{
}

fgvm::Value* CodeBuilder::createValue(std::string name, fgvm::Type* content)
{
	fgvm::SARValue* value = new fgvm::SARValue(name, content, module_container);
	this->module_container->addVariable(name, value);
	return value;
}


// hmmm
fgvm::Value* CodeBuilder::createAdd(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	// L, R must be of the same type

	fgvm::FunctionCallValue* fcall = new fgvm::FunctionCallValue(name, "add", { L, R }, this->module_container);
	// AtomicTypes::Value* value = new AtomicTypes::Value(name, content, module_container, parent);
	// this->module_container->addVariable(name, value);
	return fcall;
}