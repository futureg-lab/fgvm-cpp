#include "Module.h"


void fgvm::Module::addPool(Statement* ptr)
{
	this->ptr_pool.insert(ptr);
}

unsigned long long fgvm::Module::getId()
{
	return rand();
}

fgvm::Module::~Module()
{
	for (auto ptr : ptr_pool)
		delete ptr;
}