#include "Module.h"

// Module
void fgvm::Module::addVariable(std::string name, Value* value)
{
	variables[name] = value;
}

fgvm::Value* fgvm::Module::getVariable(std::string name)
{
	if (variables.find(name) != variables.end())
		return variables[name];
	return nullptr;
}

unsigned long long fgvm::Module::getId()
{
	return 0;
}

fgvm::Module::~Module()
{
	for (auto& [name, value] : variables)
		delete value;
}