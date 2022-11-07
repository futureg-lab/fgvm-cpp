#include "FunctionCallValue.h"

fgvm::FunctionCallValue::FunctionCallValue(std::string assign_name, std::string called_func_name, std::vector<Value*> arg_inputs)
	: FunctionCustomCallValue(assign_name, called_func_name, arg_inputs, fgvm::EType::Void)
{
	this->called_func_name = called_func_name;
	this->arg_inputs = arg_inputs;

	if (arg_inputs.size() > 0) {
		EType expected = arg_inputs[0]->expectedReductionTypeID();
		for (auto arg : arg_inputs) {
			FGError::NOT_NULL(arg);
			if (expected != arg->expectedReductionTypeID())
				throw FGError::typeMismatch("argument not of the same type", expected, arg->expectedReductionTypeID());
		}
	}
	
	// set return type
	setReductionTypeId(arg_inputs[0]->expectedReductionTypeID());
}

fgvm::EValueType fgvm::FunctionCallValue::valueTypeID() const
{
	return EValueType::FunctionCallID;
}

fgvm::EType fgvm::FunctionCallValue::expectedReductionTypeID() const
{
	if (arg_inputs.size() == 0)
		return EType::Void;
	if (arg_inputs[0]->valueTypeID() == fgvm::AssignRefID) {
		fgvm::SARRefValue* ref = dynamic_cast<fgvm::SARRefValue*>(arg_inputs[0]);
		return ref->derefValue()->expectedReductionTypeID();
	}
	return arg_inputs[0]->expectedReductionTypeID();
}