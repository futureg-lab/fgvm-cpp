#include "FunctionCustomCallValue.h"
#include "../utils/FGError.h"

fgvm::FunctionCustomCallValue::FunctionCustomCallValue(
	std::string assign_name, 
	std::string called_func_name, 
	std::vector<Value*> arg_inputs, 
	EType type_output_hint)
	: Value(assign_name)
{
	this->called_func_name = called_func_name;
	this->arg_inputs = arg_inputs;

	if (arg_inputs.size() > 0)
		for (auto arg : arg_inputs)
			FGError::NOT_NULL(arg);

	setReductionTypeId(type_output_hint);
}

void fgvm::FunctionCustomCallValue::setReductionTypeId(fgvm::EType type_output_hint)
{
	this->type_output_hint = type_output_hint;
	if (type_output_hint == fgvm::EType::Unknown)
		throw FGError::notAllowed("type not specified", "Unknown is not a valid type, use void instead");
}

fgvm::EValueType fgvm::FunctionCustomCallValue::valueTypeID() const
{
	return EValueType::FunctionCustomCallID;
}

fgvm::EType fgvm::FunctionCustomCallValue::expectedReductionTypeID() const
{
	return type_output_hint;
}