#include "CodeBuilder.h"
#include "../utils/IRUtils.h"

// private methods
fgvm::Value* fgvm::CodeBuilder::createBinaryFunc(std::string fcall_name, std::string name, fgvm::Value* L, fgvm::Value* R)
{
	// L, R must be of the same type
	auto fcall = new fgvm::FunctionCallValue(name, fcall_name, { L, R });
	registerToModuleObjectPool(fcall);
	return fcall;
}

fgvm::Value* fgvm::CodeBuilder::createUnaryFunc(std::string fcall_name, std::string name, fgvm::Value* input)
{
	auto fcall = new fgvm::FunctionCallValue(name, fcall_name, { input });
	registerToModuleObjectPool(fcall);
	return fcall;
}

void fgvm::CodeBuilder::registerToModuleObjectPool(fgvm::Statement* addr)
{
	this->module_container->addPool(addr);
}

// constructor
fgvm::CodeBuilder::CodeBuilder(fgvm::Module* module_container)
{
	this->module_container = module_container;
	FGError::NOT_NULL(module_container);
}

// destructor
fgvm::CodeBuilder::~CodeBuilder()
{
}


// Public methods

fgvm::SARValue* fgvm::CodeBuilder::createValue(std::string name, fgvm::Type* content)
{
	auto value = new fgvm::SARValue(name, content);
	registerToModuleObjectPool(value);
	return value;
}

fgvm::FArgValue* fgvm::CodeBuilder::createArg(std::string name, fgvm::EType type_hint_id)
{
	fgvm::Type* type = IRUtils::getTypeById(type_hint_id);
	fgvm::FArgValue* arg = new fgvm::FArgValue(name, type);
	registerToModuleObjectPool(arg);
	return arg;
}

fgvm::SARRefValue* fgvm::CodeBuilder::createGetAddrOf(std::string name, fgvm::Value* value)
{
	fgvm::SARRefValue* ref_value = new fgvm::SARRefValue(name, value);
	registerToModuleObjectPool(ref_value);
	return ref_value;
}

fgvm::Value* fgvm::CodeBuilder::createAlloc(std::string name, fgvm::Value* mem_size)
{
	if (mem_size->expectedReductionTypeID() != fgvm::EType::Uint32) {
		auto expected = fgvm::EType::Uint32;
		auto got = mem_size->expectedReductionTypeID();
		throw FGError::typeMismatch("invalid allocation query", expected, got);
	}
	auto fcall = createUnaryFunc("alloc", name, mem_size);
	return fcall;
}

fgvm::Value* fgvm::CodeBuilder::createSetValAddr(std::string name, fgvm::Value* ref, fgvm::Value* value)
{
	if (ref->expectedReductionTypeID() != fgvm::EType::Uint32) {
		auto expected = fgvm::EType::Uint32;
		auto got = ref->expectedReductionTypeID();
		throw FGError::typeMismatch("invalid reference address type reduction", expected, got);
	}
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "set_val_addr", { ref, value }, fgvm::EType::Uint32);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createGetValAddr(std::string name, fgvm::SARRefValue* ref)
{
	auto fcall = new fgvm::FunctionCallValue(name, "get_val_addr", { ref });
	registerToModuleObjectPool(fcall);
	return fcall;
}

fgvm::Value* fgvm::CodeBuilder::createGetValAddr(std::string name, fgvm::Value* ref, EType type_output_hint)
{
	if (ref->expectedReductionTypeID() != fgvm::EType::Uint32) {
		auto expected = fgvm::EType::Uint32;
		auto got = ref->expectedReductionTypeID();
		throw FGError::typeMismatch("invalid reference address type reduction", expected, got);
	}
	auto fcall = new fgvm::FunctionCustomCallValue(name, "get_val_addr", { ref }, type_output_hint);
	registerToModuleObjectPool(fcall);
	return fcall;
}

fgvm::RetValue* fgvm::CodeBuilder::createReturn(fgvm::Value* value)
{
	fgvm::RetValue* ret = new fgvm::RetValue(value);
	registerToModuleObjectPool(ret);
	return ret;
}



fgvm::Value* fgvm::CodeBuilder::createAdd(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("add", name, L, R);
}

fgvm::Value* fgvm::CodeBuilder::createSub(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("sub", name, L, R);
}

fgvm::Value* fgvm::CodeBuilder::createDiv(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("div", name, L, R);
}

fgvm::Value* fgvm::CodeBuilder::createMult(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	return createBinaryFunc("mult", name, L, R);
}

fgvm::Value* fgvm::CodeBuilder::createIncr(fgvm::Value* value)
{
	if (!IRUtils::isNumber(value->expectedReductionTypeID())) {
		std::string type_str = IRUtils::enumTypeToStr(value->expectedReductionTypeID());
		throw FGError::notAllowed("increment type " + type_str, "not a number");
	}
	auto fcall = createUnaryFunc("incr", value->name, value);
	return fcall;
}

fgvm::Value* fgvm::CodeBuilder::createDecr(fgvm::Value* value)
{
	if (!IRUtils::isNumber(value->expectedReductionTypeID())) {
		std::string type_str = IRUtils::enumTypeToStr(value->expectedReductionTypeID());
		throw FGError::notAllowed("decrement type " + type_str, "not a number");
	}
	auto fcall = createUnaryFunc("decr", value->name, value);
	return fcall;
}

fgvm::Value* fgvm::CodeBuilder::createCompEQ(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	if (L->expectedReductionTypeID() != R->expectedReductionTypeID())
		throw FGError::typeMismatch("\"eq\" arguments not of the same type", L->expectedReductionTypeID(), R->expectedReductionTypeID());

	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "eq", { L, R }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createCompNOTEQ(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	if (L->expectedReductionTypeID() != R->expectedReductionTypeID())
		throw FGError::typeMismatch("\"not_eq\" arguments not of the same type", L->expectedReductionTypeID(), R->expectedReductionTypeID());

	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "not_eq", { L, R }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createCompGTEQ(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	if (L->expectedReductionTypeID() != R->expectedReductionTypeID())
		throw FGError::typeMismatch("\"gte\" arguments not of the same type", L->expectedReductionTypeID(), R->expectedReductionTypeID());
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "gte", { L, R }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createCompLTEQ(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	if (L->expectedReductionTypeID() != R->expectedReductionTypeID())
		throw FGError::typeMismatch("\"lte\" arguments not of the same type", L->expectedReductionTypeID(), R->expectedReductionTypeID());
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "lte", { L, R }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createCompLT(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	if (L->expectedReductionTypeID() != R->expectedReductionTypeID())
		throw FGError::typeMismatch("\"lt\" arguments not of the same type", L->expectedReductionTypeID(), R->expectedReductionTypeID());
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "lt", { L, R }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createCompGT(std::string name, fgvm::Value* L, fgvm::Value* R)
{
	if (L->expectedReductionTypeID() != R->expectedReductionTypeID())
		throw FGError::typeMismatch("\"gt\" arguments not of the same type", L->expectedReductionTypeID(), R->expectedReductionTypeID());
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "gt", { L, R }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}


// Bloc


fgvm::FunctionDef* fgvm::CodeBuilder::createFunc(std::string name, std::vector<fgvm::FArgValue*> args, fgvm::Bloc* bloc, fgvm::EType exp_ret_type)
{
	fgvm::FunctionDef* def = new fgvm::FunctionDef(name, args, bloc, exp_ret_type);
	registerToModuleObjectPool(def);

	if (bloc->getRetValue() == nullptr)
		throw FGError::invalidReturn("function " + name, def->ret_type, fgvm::EType::Unknown);

	if (def->ret_type != bloc->getRetValue()->expectedReductionTypeID()) {
		auto exp = def->ret_type;
		auto got = bloc->getRetValue()->expectedReductionTypeID();
		throw FGError::typeMismatch("function " + name, exp, got);
	}

	return def;
}

fgvm::Bloc* fgvm::CodeBuilder::createBloc(std::string name)
{
	fgvm::Bloc* bloc = new fgvm::Bloc(name);
	registerToModuleObjectPool(bloc);
	return bloc;
}

fgvm::ConditionalBr* fgvm::CodeBuilder::createIF(fgvm::Value* condition, fgvm::Bloc* if_bloc, fgvm::Bloc* else_bloc)
{
	fgvm::ConditionalBr* cond = new fgvm::ConditionalBr(condition, if_bloc, else_bloc);
	registerToModuleObjectPool(cond);
	FGError::NOT_NULL(cond->true_bloc);
	FGError::NOT_NULL(cond->condition);
	// FGError::NOT_NULL(cond->else_bloc);
	return cond;
}

fgvm::Loop* fgvm::CodeBuilder::createLoop(fgvm::Value* condition, fgvm::Bloc* bloc)
{
	fgvm::Loop* loop = new fgvm::Loop(condition, bloc);
	registerToModuleObjectPool(loop);
	return loop;
}


// Standard I/O


fgvm::Value* fgvm::CodeBuilder::createStdout(std::string name, fgvm::Value* value)
{
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "stdout_print", { value }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createStderr(std::string name, fgvm::Value* value)
{
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "stderr_print", { value }, fgvm::EType::Bool);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}

fgvm::Value* fgvm::CodeBuilder::createStdin(std::string name, fgvm::EType type_hint)
{
	auto fcustomcall = new fgvm::FunctionCustomCallValue(name, "stderr_out", {}, type_hint);
	registerToModuleObjectPool(fcustomcall);
	return fcustomcall;
}
