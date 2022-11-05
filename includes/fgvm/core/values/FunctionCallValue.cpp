#include "FunctionCallValue.h"

fgvm::FunctionCallValue::FunctionCallValue(std::string assign_name, std::string called_func_name, std::vector<Value*> arg_inputs)
	: Value(assign_name)
{
	this->called_func_name = called_func_name;
	this->arg_inputs = arg_inputs;

	if (arg_inputs.size() > 0) {
		EType expected = arg_inputs[0]->expectedReductionTypeID();
		for (auto arg : arg_inputs) {
			FGError::NOT_NULL(arg);
			FGError::ASSERT(expected == arg->expectedReductionTypeID());
		}
	}
}

fgvm::EValueType fgvm::FunctionCallValue::valueTypeID() const
{
	return EValueType::FunctionCallID;
}

fgvm::EType fgvm::FunctionCallValue::expectedReductionTypeID() const
{
	if (arg_inputs.size() == 0)
		return EType::Void;
	return arg_inputs[0]->expectedReductionTypeID();
}