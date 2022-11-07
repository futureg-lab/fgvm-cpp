#include "CodeBuilder.h"

// private methods
fgvm::Value* CodeBuilder::createBinaryFunc(std::string fcall_name, std::string name, fgvm::Value* L, fgvm::Value* R)
{
	// L, R must be of the same type
	auto fcall = new fgvm::FunctionCallValue(name, fcall_name, { L, R });
	registerToSymbolTable(fcall);
	return fcall;
}

fgvm::Value* CodeBuilder::createUnaryFunc(std::string fcall_name, std::string name, fgvm::Value* input)
{
	auto fcall = new fgvm::FunctionCallValue(name, fcall_name, { input });
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
fgvm::SARValue* CodeBuilder::createValue(std::string name, fgvm::Type* content)
{
	auto value = new fgvm::SARValue(name, content);
	registerToSymbolTable(value);
	return value;
}

fgvm::FArgValue* CodeBuilder::createArg(std::string name, fgvm::EType type_hint_id)
{
	fgvm::Type* type = IRUtils::getTypeById(type_hint_id);
	fgvm::FArgValue* arg = new fgvm::FArgValue(name, type);
	registerToModuleObjectPool(arg);
	return arg;
}

fgvm::SARRefValue* CodeBuilder::createRef(std::string name, fgvm::Value* value)
{
	fgvm::SARRefValue* ref_value = new fgvm::SARRefValue(name, value);
	registerToSymbolTable(ref_value);
	return ref_value;
}

fgvm::Value* CodeBuilder::createAlloc(std::string name, fgvm::Value* mem_size)
{
	if (mem_size->expectedReductionTypeID() != fgvm::EType::Uint32) {
		auto expected = fgvm::EType::Uint32;
		auto got = mem_size->expectedReductionTypeID();
		throw FGError::typeMismatch("invalid allocation query", expected, got);
	}
	auto fcall = createUnaryFunc("alloc", name, mem_size);
	return fcall;
}

fgvm::Value* CodeBuilder::createGetRefAt(std::string name, fgvm::SARRefValue* ref, fgvm::Value* offset)
{
	auto fcall = createBinaryFunc("ref_offset", name, ref, offset);
	return fcall;
}

fgvm::Value* CodeBuilder::createSetRef(std::string name, fgvm::Value* ref_or_addr, fgvm::Value* value)
{
	if (ref_or_addr->expectedReductionTypeID() != fgvm::EType::Uint32) {
		auto expected = fgvm::EType::Uint32;
		auto got = ref_or_addr->expectedReductionTypeID();
		throw FGError::typeMismatch("invalid reference address type reduction", expected, got);
	}
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "set_ref", { ref_or_addr, value }, fgvm::EType::Uint32);
	return fcustomcall;
}

fgvm::RetValue* CodeBuilder::createReturn(fgvm::Value* value)
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

fgvm::Value* CodeBuilder::createDeref(std::string name, fgvm::SARRefValue* ref)
{
	auto fcall = new fgvm::FunctionCallValue(name, "deref", {ref});
	registerToSymbolTable(fcall);
	return fcall;
}

fgvm::FunctionDef* CodeBuilder::createFunc(std::string name, std::vector<fgvm::FArgValue*> args, fgvm::Bloc* bloc, fgvm::EType exp_ret_type)
{
	fgvm::FunctionDef* def = new fgvm::FunctionDef(name, args, bloc, exp_ret_type);
	
	if (bloc->getRetValue() == nullptr)
		throw FGError::invalidReturn("function " + name, def->ret_type, fgvm::EType::Unknown);

	if (def->ret_type != bloc->getRetValue()->expectedReductionTypeID()) {
		auto exp = def->ret_type;
		auto got = bloc->getRetValue()->expectedReductionTypeID();
		throw FGError::typeMismatch("function " + name, exp, got);
	}

	registerToModuleObjectPool(def);
	return def;
}

fgvm::Bloc* CodeBuilder::createBloc(std::string name)
{
	fgvm::Bloc* bloc = new fgvm::Bloc(name);
	registerToModuleObjectPool(bloc);
	return bloc;
}