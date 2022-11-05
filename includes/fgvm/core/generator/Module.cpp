#include "Module.h"

// Module
void fgvm::Module::addVariable(std::string name, Value* value)
{
	variables[name] = value;
}

void fgvm::Module::addPool(Statement* ptr)
{
	this->ptr_pool.push_back(ptr);
}

fgvm::Value* fgvm::Module::getVariable(std::string name)
{
	if (variables.find(name) != variables.end())
		return variables[name];
	return nullptr;
}

unsigned long long fgvm::Module::getId()
{
	return rand();
}

fgvm::Module::~Module()
{
	for (auto ptr : ptr_pool)
		delete ptr;
	for (auto& [name, value] : variables)
		delete value;
}