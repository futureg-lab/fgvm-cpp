#include "CodeBuilder.h"

// private methods
fgvm::Value* CodeBuilder::createBinaryFunc(std::string fcall_name, std::string name, fgvm::Value* L, fgvm::Value* R)
{
	// L, R must be of the same type
	auto fcall = new fgvm::FunctionCallValue(name, fcall_name, { L, R });
	registerToSymbolTable(fcall);
	return fcall;
}

void CodeBuilder::registerToModuleObjectPool(fgvm::Statement* addr)
{
	this->module_container->addPool(addr);
}

void CodeBuilder::registerToSymbolTable(fgvm::Value* value)
{
	this->module_container->addVariable(value->name, value);
}

// constructor
CodeBuilder::CodeBuilder(fgvm::Module* module_container)
{
	this->module_container = module_container;
	FGError::NOT_NULL(module_container);
}

// destructor
CodeBuilder::~CodeBuilder()
{
}


// public methods
fgvm::Value* CodeBuilder::createValue(std::string name, fgvm::Type* content)
{
	auto value = new fgvm::SARValue(name, content);
	registerToSymbolTable(value);
	return value;
}

fgvm::Value* CodeBuilder::createArg(std::string name, fgvm::EType type_hint_id)
{
	fgvm::Type* type = IRUtils::getTypeById(type_hint_id);
	fgvm::FArgValue* arg = new fgvm::FArgValue(name, type);
	return arg;
}

fgvm::Value* CodeBuilder::createRef(std::string name, fgvm::Value* value)
{
	fgvm::SARRefValue* ref_value = new fgvm::SARRefValue(name, value);
	return ref_value;
}

fgvm::Value* CodeBuilder::createReturn(fgvm::Value* value)
{
	fgvm::RetValue* ret = new fgvm::RetValue(value);
	registerToModuleObjectPool(ret);
	return ret;
}



fgvm::Value* CodeBuilder::createAdd(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("add", name, L, R);
}

fgvm::Value* CodeBuilder::createSub(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("sub", name, L, R);
}

fgvm::Value* CodeBuilder::createDiv(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("div", name, L, R);
}

fgvm::Value* CodeBuilder::createMult(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("mult", name, L, R);
}

fgvm::Statement* CodeBuilder::createFunc(std::string name, std::vector<fgvm::FArgValue*> args, fgvm::Bloc* bloc)
{
	fgvm::FunctionDef* def = new fgvm::FunctionDef(name, args, bloc, fgvm::EType::Void);
	FGError::ASSERT(def->ret_type == bloc->getRetValue()->expectedReductionTypeID());
	registerToModuleObjectPool(def);
	return def;
}

fgvm::Statement* CodeBuilder::createBloc(std::string name)
{
	fgvm::Bloc* bloc = new fgvm::Bloc(name);
	registerToModuleObjectPool(bloc);
	return bloc;
}