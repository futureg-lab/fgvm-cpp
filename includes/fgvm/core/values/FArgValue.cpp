#include "FArgValue.h"

// FArgs
fgvm::FArgValue::FArgValue(std::string name, Type* content, Module* module_owner)
	: Value(name, module_owner)
{
	this->content = content;
	this->module_owner = module_owner;

	FGError::NOT_NULL(this->content);
}

fgvm::EValueType fgvm::FArgValue::valueTypeID() const
{
	return EValueType::FArgumentID;
}

fgvm::EType fgvm::FArgValue::expectedReductionTypeID() const
{
	return content->getTypeId();
}
