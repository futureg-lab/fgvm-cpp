#include "Value.h"


fgvm::Value::Value(std::string name, Module* module_owner)
{
	this->name = name;
	this->module_owner = module_owner;
	FGError::NOT_NULL(module_owner);
}